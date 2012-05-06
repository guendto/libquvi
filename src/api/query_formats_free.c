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

/** @file query_formats_free.c */

#include "config.h"

#include <glib.h>

#include "quvi.h"
/* -- */
#include "_quvi_s.h"
#include "_quvi_query_formats_s.h"

static void _format_free(gpointer p, gpointer userdata)
{
  g_free(p);
  p = NULL;
}

/** @brief Free all of memory used by a query formats handle
@note If handle is NULL the function simply returns
@ingroup queryformats
*/
void quvi_query_formats_free(quvi_query_formats_t handle)
{
  _quvi_query_formats_t qf = (_quvi_query_formats_t) handle;

  if (qf == NULL)
    return;

#ifdef HAVE_GLIB_2_28
  g_slist_free_full(qf->formats, _format_free);
#else
  g_slist_foreach(qf->formats, _format_free, NULL);
  g_slist_free(qf->formats);
#endif
  qf->formats = NULL;

  g_free(qf);
  qf = NULL;
}

/* vim: set ts=2 sw=2 tw=72 expandtab: */
