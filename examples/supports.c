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

#include "config.h"

#include <locale.h>
#include <stdlib.h>
#include <string.h>
#include <glib.h>
#include <quvi.h>

#include "examples.h"

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

/* Exit status: 1=error or nosupport, otherwise 0. */
gint main(gint argc, gchar **argv)
{
  gchar *url = NULL;
  gint rc = 0;
  gint i = 1;

  g_assert(q == NULL);
  setlocale(LC_ALL, "");

  if (argc <2)
    usage();

  q = quvi_new();
  examples_exit_if_error();

  for (; i<argc; ++i)
    {
      const gchar *arg = argv[i];

      if (g_strcmp0("-s", arg) == 0)
        m = QUVI_SUPPORTS_MODE_ONLINE;

      else if (g_strcmp0("-v", arg) == 0)
        examples_enable_verbose();

      else if (g_strcmp0("-a", argv[i]) == 0)
        examples_enable_autoproxy();

      else if (g_str_has_prefix(arg, "-t") == TRUE)
        {
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
        }
      else
        url = (gchar*) arg;
    }

  if (url == NULL)
    {
      g_printerr("[%s] error: URL required\n", __func__);
      examples_cleanup();
      return (2);
    }

  t = (t == 0) ? QUVI_SUPPORTS_TYPE_MEDIA : t;

  g_printerr("[%s] mode=0x%x\n", __func__, (gint) m);
  g_printerr("[%s] type=0x%x\n", __func__, (gint) t);

  quvi_set(q, QUVI_OPTION_CALLBACK_STATUS, (qcs) examples_status);
  {
    const QuviBoolean r = quvi_supports(q, url, m, t);

    /* Always check for any network errors with QUVI_SUPPORTS_MODE_ONLINE. */
    if (r == FALSE && m == QUVI_SUPPORTS_MODE_ONLINE)
      {
        glong ec = 0;
        quvi_get(q, QUVI_INFO_ERROR_CODE, &ec);

        if (ec != QUVI_ERROR_NO_SUPPORT) /* Ignore "no support". */
          g_printerr("\nerror: %s\n", quvi_errmsg(q));
      }
    else
      g_print("%s : %s\n", url, (r == QUVI_TRUE) ? "yes":"no");

    rc = (r == QUVI_TRUE) ? 0:1;
  }
  examples_cleanup();
  g_assert(q == NULL);

  return (rc);
}

/* vim: set ts=2 sw=2 tw=72 expandtab: */
