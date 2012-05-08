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

#include <stdlib.h>
#include <glib.h>
#include <quvi.h>

static void usage()
{
  g_printerr("Usage: scan <URL>\n");
  exit(0);
}

extern QuviError status(glong, gpointer);
extern void exit_if_error();
extern void cleanup();

typedef quvi_callback_status qcs;

extern quvi_scan_t qs;
extern quvi_t q;

int main(int argc, char **argv)
{
  g_assert(qs == NULL);
  g_assert(q == NULL);

  if (argc < 2)
    usage();

  q = quvi_new();
  exit_if_error();

  quvi_set(q, QUVI_OPTION_CALLBACK_STATUS, (qcs) status);

  qs = quvi_scan_new(q, argv[1]);
  exit_if_error();
  {
    const gchar *s = NULL;
    while ((s = quvi_scan_next_media_url(qs)) != NULL)
      g_print("%s\n", s);
  }

  cleanup();

  g_assert(qs == NULL);
  g_assert(q == NULL);

  return (0);
}

/* vim: set ts=2 sw=2 tw=72 expandtab: */
