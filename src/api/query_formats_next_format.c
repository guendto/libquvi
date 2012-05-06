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

/** @file query_formats_next_format.c */

#include "config.h"

#include <glib.h>

#include "quvi.h"
/* -- */
#include "_quvi_s.h"
#include "_quvi_query_formats_s.h"

/** @return Next available format (NULL-terminated) string or NULL
@note Do not attempt to free the returned string
@sa @ref query_formats
@ingroup queryformats
*/
const char *quvi_query_formats_next_format(quvi_query_formats_t handle)
{
  _quvi_query_formats_t qf = (_quvi_query_formats_t) handle;

  /* If G_DISABLE_CHECKS is defined then the check is not performed. */
  g_return_val_if_fail(handle != NULL, NULL);

  qf->curr.format = (qf->curr.format != NULL)
                    ? g_slist_next(qf->curr.format)
                    : qf->formats;

  return ((qf->curr.format != NULL)
          ? qf->curr.format->data
          : NULL);
}

/* vim: set ts=2 sw=2 tw=72 expandtab: */
