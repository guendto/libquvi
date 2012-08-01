/* libquvi
 * Copyright (C) 2012  Toni Gundogdu <legatvs@gmail.com>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
 * 02110-1301, USA.
 */

#include "config.h"

#include <lauxlib.h>
#include <glib.h>

#include "quvi.h"
/* -- */
#include "_quvi_s.h"
#include "_quvi_verify_s.h"
#include "_quvi_net_s.h"
#include "_quvi_macro.h"
/* -- */
#include "net/handle.h"
#include "net/opt.h"

extern QuviError l_exec_util_to_file_ext(_quvi_verify_t, _quvi_net_t);
extern QuviError c_verify(_quvi_t, _quvi_net_t);

static const gdouble MIN_LIKELY_MEDIA_LENGTH = 50*1024;

static QuviError _verify(_quvi_verify_t v)
{
  _quvi_net_t n;
  QuviError rc;
  lua_State *l;
  _quvi_t q;

  q = v->handle.quvi;
  n = n_new(q, v->url.input->str);
  l = q->handle.lua;

  if (lua_istable(l, 2))
    n_chk_callback_opts(n, l);

  if (q->cb.verify != NULL)
    rc = q->cb.verify(n);
  else
    rc = c_verify(q, n); /* Verify using cURL (default). */

  if (rc == QUVI_OK)
    {
      rc = l_exec_util_to_file_ext(v, n);
      if (rc == QUVI_OK)
        {
          g_string_assign(v->content_type, n->verify.content_type->str);
          v->length_bytes = n->verify.content_length;
        }

      if (q->cb.status != NULL)
        {
          const glong p = q_makelong(QUVI_CALLBACK_STATUS_VERIFY,
                                     QUVI_CALLBACK_STATUS_DONE);

          if (q->cb.status(p, 0) != QUVI_OK)
            rc = QUVI_ERROR_CALLBACK_ABORTED;
        }
    }
  else
    {
      /* Save returned error message. */
      if (n->status.errmsg->len >0)
        g_string_assign(q->status.errmsg, n->status.errmsg->str);
      else
        {
          g_string_assign(q->status.errmsg,
                          "Unknown error: verify: callback returned "
                          "an empty errmsg");
        }
    }

  q->status.resp_code = n->status.resp_code;
  n_free(n);

  return (rc);
}

QuviError n_verify(_quvi_verify_t v)
{
  _quvi_t q;
  gchar *s;

  q = v->handle.quvi;
  s = g_uri_parse_scheme(v->url.input->str);

  if (s != NULL) /* Verify HTTP(S) media stream URLs only. */
    {
      const gboolean r = (gboolean) g_strcmp0(s, "http") == 0
                         || g_strcmp0(s, "https") == 0;

      g_free(s);
      s = NULL;

      if (r == FALSE)
        return (QUVI_OK); /* Skip verification. */
    }
  else
    {
      g_string_printf(q->status.errmsg,
                      "Unable to parse URI: %s", v->url.input->str);
      return (QUVI_ERROR_INVALID_ARG); /* Skip verification. */
    }

  if (q->cb.status != NULL)
    {
      const glong p = q_makelong(QUVI_CALLBACK_STATUS_VERIFY, 0);

      if (q->cb.status(p, 0) != QUVI_OK)
        return (QUVI_ERROR_CALLBACK_ABORTED);
    }

  return (_verify(v));
}

/* vim: set ts=2 sw=2 tw=72 expandtab: */
