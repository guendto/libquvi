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

#include <string.h>
#include <glib.h>
/* -- */
#include "temp.h"

_c_temp_t c_temp_new()
{
  _c_temp_t t = g_new0(struct _c_temp_s, 1);
  return (t);
}

void c_temp_free(_c_temp_t p)
{
  if (p == NULL)
    return;

  g_free(p->p);
  p->p =  NULL;

  g_free(p);
  p = NULL;
}

/* cURL write callback. Uses "tmp" handle for storing data. */
gsize c_temp_wrcb(gpointer p, gsize sz, gsize nmemb, gpointer d)
{
  const gsize rsize = sz * nmemb;
  _c_temp_t t = (_c_temp_t) d;
  gpointer *tmp = g_realloc(t->p, t->size+rsize+1);
  if (tmp != NULL)
    {
      t->p = (gchar*) tmp;
      memcpy(&(t->p[t->size]), p, rsize);
      t->size += rsize;
      t->p[t->size] = '\0';
    }
  return (rsize);
}

/* vim: set ts=2 sw=2 tw=72 expandtab: */
