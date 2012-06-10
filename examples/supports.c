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
#include <string.h>
#include <glib.h>
#include <quvi.h>

static void usage()
{
  g_printerr(
    "Usage: supports [options] <URL>\n"
    "\nOptions:\n"
    "  -t<value> .. Support type ('m'edia,'p'laylist,'a'ny)\n"
    "  -s        .. Run online\n"
    "\nExample:\n"
    "  supports -s -tp URL ;# Check (online) against playlist scripts\n"
    "  supports -ta URL    ;# Check against all types of scripts\n"
    "\nNote: Checking online resolves shortened URLs, e.g. redirections\n");
  exit(0);
}

extern QuviError status(glong, gpointer);
extern void exit_if_error();
extern void cleanup();

typedef quvi_callback_status qcs;

static QuviSupportsMode m = QUVI_SUPPORTS_MODE_OFFLINE;
static QuviSupportsType t = 0;

static void update_type(gchar c)
{
  switch (c)
    {
    case 'p':
      t |= QUVI_SUPPORTS_TYPE_PLAYLIST;
      break;
    case 'm':
      t |= QUVI_SUPPORTS_TYPE_MEDIA;
      break;
    case 'a':
      t = QUVI_SUPPORTS_TYPE_ANY;
      break;
    default:
      g_printerr("[%s]: ignored `%c': unknown type\n", __func__, c);
      break;
    }
}

extern quvi_t q;

gint main(gint argc, gchar **argv)
{
  gchar *url = NULL;
  gint rc = 0;
  gint i = 1;

  g_assert(q == NULL);

  if (argc <2)
    usage();

  for (; i<argc; ++i)
    {
      const gchar *arg = argv[i];
      if (arg[0] == '-')
        {
          switch (arg[1])
            {
            case 's':
              m = QUVI_SUPPORTS_MODE_ONLINE;
              break;
            case 't':
              if (strlen(arg) >1)
                {
                  gchar *p = (gchar*) &arg[2];
                  while (*p != '\0')
                    {
                      update_type(*p);
                      ++p;
                    }
                }
              else
                t = QUVI_SUPPORTS_TYPE_MEDIA;
              break;
            }
        }
      else
        url = (gchar*) arg;
    }

  if (url == NULL)
    {
      g_printerr("[%s] error: URL required\n", __func__);
      return (2);
    }

  t = (t == 0) ? QUVI_SUPPORTS_TYPE_MEDIA : t;

  g_printerr("[%s] mode=0x%x\n", __func__, (gint) m);
  g_printerr("[%s] type=0x%x\n", __func__, (gint) t);

  q = quvi_new();
  exit_if_error();

  quvi_set(q, QUVI_OPTION_CALLBACK_STATUS, (qcs) status);
  {
    QuviBoolean r = quvi_supports(q, url, m, t);
    g_print("%s : %s\n", url, (r == QUVI_TRUE) ? "yes":"no");
    rc = (r == QUVI_TRUE) ? 1:0;
  }
  cleanup();
  g_assert(q == NULL);

  return (rc);
}

/* vim: set ts=2 sw=2 tw=72 expandtab: */
