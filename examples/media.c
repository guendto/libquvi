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

#include <glib.h>
#include "quvi.h"

quvi_media_t qm = NULL;
quvi_t q = NULL;

extern void exit_if_error();
extern void cleanup();

static const gchar URL[] =
  "http://www.break.com/index/happy-easter-from-kate-upton-2316293";

int main(int argc, char **argv)
{
  q = quvi_new();
  exit_if_error();
  qm = quvi_media_new(q, (gchar*) URL);
  exit_if_error();
  {
    gchar *s = NULL;
    quvi_media_get(qm, QUVI_MEDIA_PROPERTY_TITLE, &s);
    g_print("%s\n", s);
  }
  cleanup();
  return (0);
}

/* vim: set ts=2 sw=2 tw=72 expandtab: */
