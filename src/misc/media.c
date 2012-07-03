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
#include "misc/media.h"

gpointer m_media_new(_quvi_t q, const gchar *url)
{
  _quvi_media_t m = g_new0(struct _quvi_media_s, 1);
  /* URL */
  m->url.redirect_to = g_string_new(NULL);
  m->url.thumbnail = g_string_new(NULL);
  m->url.stream = g_string_new(NULL);
  m->url.input = g_string_new(url);
  /* Handle */
  m->handle.quvi = q;
  /* Other */
  m->content_type = g_string_new(NULL);
  m->file_ext = g_string_new(NULL);
  m->title = g_string_new(NULL);
  m->id = g_string_new(NULL);
  return (m);
}

void m_media_free(_quvi_media_t m)
{
  if (m == NULL)
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

  /* Other */

  g_string_free(m->content_type, TRUE);
  m->content_type = NULL;

  g_string_free(m->file_ext, TRUE);
  m->file_ext= NULL;

  g_string_free(m->title, TRUE);
  m->title = NULL;

  g_string_free(m->id, TRUE);
  m->id = NULL;

  g_free(m);
  m = NULL;
}

/* vim: set ts=2 sw=2 tw=72 expandtab: */
