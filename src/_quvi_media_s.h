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

#ifndef _quvi_media_s_h
#define _quvi_media_s_h

struct _quvi_media_s
{
  struct
  {
    GString *redirect_to; /* Set in a media script ("goto_url") */
    GString *thumbnail;
    GString *stream;
    GString *input; /* e.g. "http://youtube.com/?watch=foo" */
  } url;
  struct
  {
    _quvi_t quvi;
  } handle;
  /* Other */
  GString *content_type;
  gdouble start_time_ms;
  gdouble length_bytes;
  gdouble duration_ms;
  GString *file_ext;
  GString *title;
  GString *id;
};

typedef struct _quvi_media_s *_quvi_media_t;

#endif /* _quvi_media_s_h */

/* vim: set ts=2 sw=2 tw=72 expandtab: */
