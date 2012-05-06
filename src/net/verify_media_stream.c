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
#include "_quvi_media_s.h"
#include "_quvi_net_s.h"
#include "_quvi_macro.h"
/* -- */
#include "net/handle.h"
#include "net/opt.h"

extern QuviError l_exec_util_to_file_ext(_quvi_media_t, _quvi_net_t);
extern QuviError c_verify(_quvi_t, _quvi_net_t);

static QuviError _verify(_quvi_media_t m)
{
  _quvi_t q = m->handle.quvi;
  lua_State *l = q->handle.lua;
  QuviError rc = QUVI_OK;
  _quvi_net_t n = NULL;

  if (g_str_has_prefix(m->url.stream->str, "htt") == FALSE)
    return (QUVI_OK); /* Ignore non-HTTP(s) media stream URLs */

  n = n_new(m->handle.quvi, m->url.stream->str);

  if (lua_istable(l, 2))
    n_chk_callback_opts(n, l);

  if (q->cb.verify != NULL)
    rc = q->cb.verify(n);
  else
    rc = c_verify(q, n); /* Verify using cURL (default). */

  if (rc == QUVI_OK)
    {
      rc = l_exec_util_to_file_ext(m, n);
      if (rc == QUVI_OK)
        {
          g_string_assign(m->content_type, n->verify.content_type->str);
          m->length_bytes = n->verify.content_length;
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
                          "unknown error: verify: callback returned "
                          "empty errmsg");
        }
    }

  q->status.resp_code = n->status.resp_code;
  n_free(n);

  return (rc);
}

QuviError n_verify_media_stream(_quvi_media_t m)
{
  _quvi_t q = m->handle.quvi;

  if (q->opt.verify == FALSE)
    return (QUVI_OK); /* Skip check if the flag is set. */

  if (q->cb.status != NULL)
    {
      const glong p = q_makelong(QUVI_CALLBACK_STATUS_VERIFY, 0);

      if (q->cb.status(p, 0) != QUVI_OK)
        return (QUVI_ERROR_CALLBACK_ABORTED);
    }

  return (_verify(m));
}

/* vim: set ts=2 sw=2 tw=72 expandtab: */
