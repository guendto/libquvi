/* libquvi
 * Copyright (C) 2012  Toni Gundogdu <legatvs@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdlib.h>
#include <glib.h>
#include <quvi.h>

static void usage()
{
  g_printerr("Usage: query_formats <URL>\n");
  exit(0);
}

extern void exit_if_error();
extern void cleanup();

quvi_query_formats_t qqf = NULL;
quvi_playlist_t qp = NULL;
quvi_media_t qm = NULL;
quvi_t q = NULL;

int main(int argc, char **argv)
{
  if (argc < 2)
    usage();

  q = quvi_new();
  exit_if_error();
  {
    qqf = quvi_query_formats_new(q, argv[1]);
    exit_if_error();
    {
      const gchar *s = NULL;
      while ((s = quvi_query_formats_next_format(qqf)) != NULL)
        g_print("%s\n", s);
    }
  }
  cleanup();

  return (0);
}

/* vim: set ts=2 sw=2 tw=72 expandtab: */
