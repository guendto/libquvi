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

/** @file scan_free.c */

#include "config.h"

#include <glib.h>

#include "quvi.h"
/* -- */
#include "_quvi_s.h"
#include "_quvi_scan_s.h"

static void _url_free(gpointer p, gpointer userdata)
{
  if (p == NULL)
    return;

  g_free(p);
  p = NULL;
}

/** @brief Free all of memory used by a scan handle
@note If handle is NULL the function simply returns
@sa @ref scan_media
@ingroup scan
*/
void quvi_scan_free(quvi_scan_t handle)
{
  _quvi_scan_t s = (_quvi_scan_t) handle;

  if (handle == NULL)
    return;

  /* URLs */

#ifdef HAVE_GLIB_2_28
  g_slist_free_full(s->url.media, _url_free);
#else
  g_slist_foreach(s->url.media, _url_free, NULL);
  g_slist_free(s->url.media);
#endif
  s->url.media = NULL;

  g_string_free(s->url.input, TRUE);
  s->url.input = NULL;

  g_free(s);
  s = NULL;
}

/* vim: set ts=2 sw=2 tw=72 expandtab: */
