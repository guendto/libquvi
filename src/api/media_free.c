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

/** @file media_free.c */

#include "config.h"

#include <glib.h>

#include "quvi.h"
/* -- */
#include "_quvi_s.h"
#include "_quvi_media_s.h"

/** @brief Free all of memory used by a media handle
@note If handle is NULL the function simply returns
@sa @ref parse_media
@ingroup mediaprop
*/
void quvi_media_free(quvi_media_t handle)
{
  _quvi_media_t m = (_quvi_media_t) handle;

  if (handle == NULL)
    return;

  /* URLs */

  g_string_free(m->url.redirect_to, TRUE);
  m->url.redirect_to = NULL;

  g_string_free(m->url.thumbnail, TRUE);
  m->url.thumbnail = NULL;

  g_string_free(m->url.stream, TRUE);
  m->url.stream = NULL;

  g_string_free(m->url.input, TRUE);
  m->url.input = NULL;

  /* IDs */

  g_string_free(m->id.media, TRUE);
  m->id.media = NULL;

  g_string_free(m->id.site, TRUE);
  m->id.site = NULL;

  /* Other */

  g_string_free(m->content_type, TRUE);
  m->content_type = NULL;

  g_string_free(m->file_ext, TRUE);
  m->file_ext= NULL;

  g_string_free(m->title, TRUE);
  m->title = NULL;

  g_free(m);
  m = NULL;
}

/* vim: set ts=2 sw=2 tw=72 expandtab: */
