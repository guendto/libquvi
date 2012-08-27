/* libquvi
 * Copyright (C) 2012  Toni Gundogdu <legatvs@gmail.com>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
 * 02110-1301  USA
 */

#ifndef _quvi_media_s_h
#define _quvi_media_s_h

struct _quvi_media_stream_s
{
  struct
  {
    gdouble bitrate_kbit_s;
    GString *encoding;
    gdouble height;
    gdouble width;
  } video;
  struct
  {
    gdouble bitrate_kbit_s;
    GString *encoding;
  } audio;
  struct
  {
    gboolean best;
  } flags;
  GString *container;
  GString *url;
  GString *id;
};

typedef struct _quvi_media_stream_s *_quvi_media_stream_t;

struct _quvi_media_s
{
  struct
  {
    GSList *stream;
  } curr;
  struct
  {
    GString *redirect_to; /* Set in a media script ("goto_url") */
    GString *thumbnail;
    GString *input; /* e.g. "http://youtube.com/?watch=foo" */
  } url;
  struct
  {
    _quvi_t quvi;
  } handle;
  /* Other */
  gdouble start_time_ms;
  gdouble duration_ms;
  GSList *streams;
  GString *title;
  GString *id;
};

typedef struct _quvi_media_s *_quvi_media_t;

#endif /* _quvi_media_s_h */

/* vim: set ts=2 sw=2 tw=72 expandtab: */
