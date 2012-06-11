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

#include <glib.h>

#include "quvi.h"
/* -- */
#include "_quvi_s.h"
#include "_quvi_macro.h"
#include "_quvi_net_resolve_s.h"
/* -- */
#include "net/resolve.h"
#include "net/handle.h"

extern QuviError c_resolve(_quvi_t, _quvi_net_resolve_t);

QuviError n_resolve(_quvi_t q, _quvi_net_resolve_t r)
{
  QuviError rc = QUVI_OK;

  if (q->cb.status != NULL)
    {
      const glong p = q_makelong(QUVI_CALLBACK_STATUS_RESOLVE, 0);

      if (q->cb.status(p, 0) != QUVI_OK)
        return (QUVI_ERROR_CALLBACK_ABORTED);
    }

  if (q->cb.resolve != NULL)
    rc = q->cb.resolve(r);
  else
    rc = c_resolve(q, r);

  if (rc == QUVI_OK)
    {
      if (q->cb.status != NULL)
        {
          const glong p = q_makelong(QUVI_CALLBACK_STATUS_RESOLVE,
                                     QUVI_CALLBACK_STATUS_DONE);

          if (q->cb.status(p, 0) != QUVI_OK)
            rc = QUVI_ERROR_CALLBACK_ABORTED;
        }
    }
  else
    {
      if (r->status.errmsg->len >0)
        g_string_assign(q->status.errmsg, r->status.errmsg->str);
      else
        {
          g_string_assign(q->status.errmsg,
                          "unknown error: callback returned empty errmsg");
        }
    }

  q->status.resp_code = r->status.resp_code;

  return (rc);
}

/* vim: set ts=2 sw=2 tw=72 expandtab: */
