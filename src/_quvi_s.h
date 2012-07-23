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

#ifndef _quvi_s_h
#define _quvi_s_h

typedef gint (*quvi_callback_fetch)(gpointer);
typedef gint (*quvi_callback_resolve)(gpointer);
typedef gint (*quvi_callback_verify)(gpointer);

struct _quvi_s
{
  struct
  {
    quvi_callback_resolve resolve;
    quvi_callback_status status;
    quvi_callback_verify verify;
    quvi_callback_fetch fetch;
  } cb;
  struct
  {
    gboolean autoproxy;
    GString *format;
    struct
    {
      gboolean verbose; /* LIBQUVI_VERBOSE_SCRIPTS */
      glong category;
    } scripts;
  } opt;
  struct
  {
    GString *errmsg;
    glong resp_code;
    QuviError rc;
  } status;
  struct
  {
    gpointer proxy;
    gpointer curl;
    gpointer lua;
  } handle;
  struct
  {
    struct
    {
      GSList *playlist;
      GSList *media;
      GSList *scan;
    } curr;
    GSList *playlist;
    GSList *media;
    GSList *scan;
    GSList *util;
  } scripts;
};

typedef struct _quvi_s *_quvi_t;

#endif /* _quvi_s_h */

/* vim: set ts=2 sw=2 tw=72 expandtab: */
