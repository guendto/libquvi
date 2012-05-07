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
  g_printerr("Usage: supports [options] <URL>\n"
             "Options:\n"
             "  -S .. Run offline\n");
  exit(0);
}

extern void exit_if_error();
extern void cleanup();

static QuviSupportsMode m = QUVI_SUPPORTS_MODE_ONLINE;
static QuviSupportsType t = QUVI_SUPPORTS_TYPE_ANY;

quvi_query_formats_t qqf = NULL;
quvi_playlist_t qp = NULL;
quvi_media_t qm = NULL;
quvi_t q = NULL;

int main(int argc, char **argv)
{
  gchar *url = NULL;
  gint rc = 0;
  gint i = 1;

  if (argc <2)
    usage();

  for (; i<argc; ++i)
    {
      if (argv[i][0] == '-')
        {
          switch (argv[i][1])
            {
            case 'S':
              m = QUVI_SUPPORTS_MODE_OFFLINE;
              break;
            }
        }
      else
        url = argv[i];
    }

  if (url == NULL)
    {
      g_printerr("[%s] error: URL required\n", __func__);
      return (2);
    }

  q = quvi_new();
  exit_if_error();
  {
    QuviBoolean r = quvi_supports(q, url, m, t);
    g_print("%s : %s\n", url, (r == QUVI_TRUE) ? "yes":"no");
    rc = (r == QUVI_TRUE) ? 1:0;
  }
  cleanup();

  return (rc);
}

/* vim: set ts=2 sw=2 tw=72 expandtab: */
