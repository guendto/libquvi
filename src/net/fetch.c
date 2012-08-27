/* libquvi
 * Copyright (C) 2012  Toni Gundogdu <legatvs@gmail.com>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
 * 02110-1301  USA
 */

#include "config.h"

#include <lauxlib.h>
#include <string.h>
#include <glib.h>

#include "quvi.h"
/* -- */
#include "_quvi_s.h"
#include "_quvi_net_s.h"
#include "_quvi_net_opt_s.h"
#include "_quvi_macro.h"
/* -- */
#include "net/def.h"
#include "net/handle.h"
#include "net/opt.h"

/* Return status type. */
static glong _cb_status_type(_quvi_net_t n)
{
  _quvi_net_opt_t o;
  GSList *curr;
  glong st;

  st = QUVI_CALLBACK_STATUS_FETCH_URL; /* default */
  curr = n->options;

  while (curr != NULL)
    {
      o = (_quvi_net_opt_t) curr->data;
      if (o->id == QUVI_FETCH_OPTION_TYPE)
        {
          st = (glong) o->value.n;
          break;
        }
      curr = g_slist_next(curr);
    }
  return (st);
}

static gchar *_chk_opt_from_charset(_quvi_net_t n)
{
  _quvi_net_opt_t o;
  GSList *curr;

  curr = n->options;
  while (curr != NULL)
    {
      o = (_quvi_net_opt_t) curr->data;

      if (o->id == QUVI_FETCH_OPTION_FROM_CHARSET)
        return (g_strdup(o->value.s->str));

      curr = g_slist_next(curr);
    }
  return (NULL);
}

extern gchar* to_utf8(const gchar*, const gchar*);
extern QuviError c_fetch(_quvi_net_t);

void n_fetch(_quvi_t q, _quvi_net_t *n, const gchar *url)
{
  *n = n_new(q, url);
  n_chk_callback_opts(*n, q->handle.lua);

  if (q->cb.status != NULL)
    {
      const glong st = _cb_status_type(*n);
      const glong p = q_makelong(QUVI_CALLBACK_STATUS_FETCH, st);

      if (q->cb.status(p, (gpointer) url) != QUVI_OK)
        {
          q->status.rc = QUVI_ERROR_CALLBACK_ABORTED;
          return;
        }
    }

  if (q->cb.fetch != NULL)
    q->status.rc = q->cb.fetch(*n);
  else /* Fetch using cURL (default). */
    q->status.rc = c_fetch(*n);

  if (quvi_ok(q) == QUVI_TRUE && (*n)->status.resp_code == 200)
    {
      /* To UTF8. */
      gchar *from = _chk_opt_from_charset(*n);
      gchar *c = to_utf8((*n)->fetch.content->str, from);

      if (c != NULL)
        {
          g_string_assign((*n)->fetch.content, c);
          g_free(c);
          c = NULL;
        }

      if (from != NULL)
        {
          g_free(from);
          from = NULL;
        }

      /* Update status. */
      if (q->cb.status != NULL)
        {
          const glong p = q_makelong(QUVI_CALLBACK_STATUS_FETCH,
                                     QUVI_CALLBACK_STATUS_DONE);

          if (q->cb.status(p, 0) != QUVI_OK)
            q->status.rc = QUVI_ERROR_CALLBACK_ABORTED;
        }
    }
  else
    {
      /* Save returned error message. */
      if ((*n)->status.errmsg->len >0)
        g_string_assign(q->status.errmsg, (*n)->status.errmsg->str);
      else
        {
          g_string_assign(q->status.errmsg,
                          "unknown error: fetch: callback returned "
                          "empty errmsg");
        }
    }

  q->status.resp_code = (*n)->status.resp_code;
}

/* vim: set ts=2 sw=2 tw=72 expandtab: */
