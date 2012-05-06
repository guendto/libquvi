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
#include "_quvi_media_s.h"
/* -- */
#include "misc/media_new.h"

gpointer m_media_new(_quvi_t q, const gchar *url)
{
  _quvi_media_t m = g_new0(struct _quvi_media_s, 1);
  /* URL */
  m->url.redirect_to = g_string_new(NULL);
  m->url.thumbnail = g_string_new(NULL);
  m->url.stream = g_string_new(NULL);
  m->url.input = g_string_new(url);
  /* ID */
  m->id.media = g_string_new(NULL);
  m->id.site  = g_string_new(NULL);
  /* Handle */
  m->handle.quvi = q;
  /* Other */
  m->content_type = g_string_new(NULL);
  m->start_time = g_string_new(NULL);
  m->file_ext = g_string_new(NULL);
  m->title = g_string_new(NULL);
  return (m);
}

/* vim: set ts=2 sw=2 tw=72 expandtab: */
