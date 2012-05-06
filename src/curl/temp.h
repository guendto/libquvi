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

#ifndef c_temp_h
#define c_temp_h

struct _c_temp_s
{
  gsize size;
  gchar *p;
};

typedef struct _c_temp_s *_c_temp_t;

_c_temp_t c_temp_new();
void  c_temp_free(_c_temp_t);
gsize c_temp_wrcb(gpointer, gsize, gsize, gpointer);

#endif /* c_temp_h */

/* vim: set ts=2 sw=2 tw=72 expandtab: */
