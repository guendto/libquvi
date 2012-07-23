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

/** @file verify_free.c */

#include "config.h"

#include <glib.h>

#include "quvi.h"
/* -- */
#include "_quvi_s.h"
#include "_quvi_verify_s.h"

/** @brief Free all of memory used by a verify handle
@note If handle is NULL the function simply returns
@ingroup verify
*/
void quvi_verify_free(quvi_verify_t handle)
{
  _quvi_verify_t v = (_quvi_verify_t) handle;

  if (handle == NULL)
    return;

  g_string_free(v->url.input, TRUE);
  v->url.input = NULL;

  g_string_free(v->content_type, TRUE);
  v->content_type = NULL;

  g_string_free(v->file_ext, TRUE);
  v->file_ext = NULL;

  g_free(v);
  v = NULL;
}

/* vim: set ts=2 sw=2 tw=72 expandtab: */
