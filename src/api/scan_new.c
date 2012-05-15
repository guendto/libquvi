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

/** @file scan_new.c */

#include "config.h"

#include <glib.h>

#include "quvi.h"
/* -- */
#include "_quvi_s.h"
#include "_quvi_net_s.h"
#include "_quvi_scan_s.h"
/* -- */
#include "net/handle.h"
#include "net/fetch.h"
#include "lua/exec.h"
#include "misc/scan_new.h"

/** @cond NODOC */
struct _exec_scan_script_s
{
  struct
  {
    _quvi_scan_t scan;
    _quvi_net_t net;
  } handle;
};

typedef struct _exec_scan_script_s *_exec_scan_script_t;

static void _exec_scan_script(gpointer p, gpointer userdata)
{
  _exec_scan_script_t ess = (_exec_scan_script_t) userdata;
  _quvi_t q = (ess != NULL) ? ess->handle.scan->handle.quvi : NULL;

  if (p == NULL || userdata == NULL)
    return;

  if (q->status.rc == QUVI_OK)
    {
      q->status.rc = l_exec_scan_script_parse(
                       ess->handle.scan, p,
                       ess->handle.net->fetch.content->str);
    }
}
/** @endcond */

/** @brief Scan URL contents for supported embedded media URLs
@note @ref quvi_scan_free the handle when done using it
@sa @ref scan_media
@ingroup scan
*/
quvi_scan_t quvi_scan_new(quvi_t handle, const char *url)
{
  _quvi_t q = (_quvi_t) handle;
  _quvi_scan_t s = NULL;

  /* If G_DISABLE_CHECKS is defined then the check is not performed. */
  g_return_val_if_fail(handle != NULL, NULL);
  g_return_val_if_fail(url != NULL, NULL);

  s = m_scan_new(q, url);
  {
    quvi_resolve_t r = quvi_resolve_new(q, url, FALSE);
    if (q->status.rc == QUVI_OK)
      {
        _quvi_net_t n = NULL;

        /* Make redirection URL new input URL. */
        if (quvi_resolve_forwarded(r) == QUVI_TRUE)
          g_string_assign(s->url.input, quvi_resolve_destination_url(r));

        n_fetch(q, &n, s->url.input->str);

        if (quvi_ok(q) == QUVI_TRUE)
          {
            struct _exec_scan_script_s e;

            e.handle.scan = s;
            e.handle.net = n;

            g_slist_foreach(q->scripts.scan, _exec_scan_script, &e);
          }
        n_free(n);
        n = NULL;
      }
    quvi_resolve_free(r);
    r = NULL;
  }
  return (s);
}

/* vim: set ts=2 sw=2 tw=72 expandtab: */
