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

#include <locale.h>
#include <stdlib.h>
#include <string.h>
#include <glib.h>
#include <quvi.h>

static void usage()
{
  g_print("Usage: script [options]\n"
          "Type\n"
          "  -p           .. Dump playlist scripts\n"
          "  -m           .. Dump media scripts [default]\n"
          "  -s           .. Dump scan scripts\n"
          "Printing\n"
          "  -t<arg> =pd  .. Property mask, where 'c', 'i', 'd'\n"
          "                   'p', 'n' and 's' are accepted\n"
         );
  exit(0);
}

static QuviScriptType type = QUVI_SCRIPT_TYPE_MEDIA;
static GString *mask = NULL;

static void parse_mask(gchar *arg)
{
  gint i=2;

  if (strlen(arg) < 3)
    return;

  mask = g_string_new(NULL);

  for (; arg[i]; ++i)
    {
      switch (arg[i])
        {
        case 'c':
        case 'i':
        case 'd':
        case 'p':
        case 'n':
        case 's':
          g_string_append_c(mask, arg[i]);
          break;
        default:
          g_printerr("[%s] Unknown property mask character `%c'\n",
                     __func__, arg[i]);
        }
    }
}

static void parse_args(gint argc, gchar **argv)
{
  gint i=1;
  for (; i<argc; ++i)
    {
      if (strlen(argv[i]) <2 || argv[i][0] != '-')
        continue;

      switch (argv[i][1])
        {
          /* Type */
        case 'p':
          type = QUVI_SCRIPT_TYPE_PLAYLIST;
          break;
        case 'm':
          type = QUVI_SCRIPT_TYPE_MEDIA;
          break;
        case 's':
          type = QUVI_SCRIPT_TYPE_SCAN;
          break;
          /* Property mask */
        case 't':
          parse_mask(argv[i]);
          break;
        default:
          usage();
        }
    }
}

static void dump_script(quvi_t q)
{
  GString *o = g_string_new("Properties:\n");
  gchar *prop = mask->str;
  gint i=0;

  for (; prop[i]; ++i)
    {
      QuviScriptProperty qsp;
      switch (prop[i])
        {
        case 'c':
          qsp = QUVI_SCRIPT_PROPERTY_CATEGORIES;
          g_string_append(o, "  c=");
          break;
        case 'p':
          qsp = QUVI_SCRIPT_PROPERTY_FILEPATH;
          g_string_append(o, "  p=");
          break;
        case 'n':
          qsp = QUVI_SCRIPT_PROPERTY_FILENAME;
          g_string_append(o, "  n=");
          break;
        case 'd':
          qsp = QUVI_SCRIPT_PROPERTY_DOMAIN;
          g_string_append(o, "  d=");
          break;
        case 's':
          qsp = QUVI_SCRIPT_PROPERTY_SHA1;
          g_string_append(o, "  s=");
          break;
        case 'i':
          qsp = QUVI_SCRIPT_PROPERTY_SITE;
          g_string_append(o, "  i=");
          break;
        default:
          g_warning("Invalid property mask character `%c'\n", prop[i]);
          continue;
        }
      {
        gchar *s = NULL;
        quvi_script_get(q, type, qsp, &s);
        g_string_append_printf(o, "%s\n", s);
      }
    }
  g_print("%s", o->str);
  g_string_free(o, TRUE);
}

extern void exit_if_error();
extern void cleanup();

extern quvi_t q;

gint main(gint argc, gchar **argv)
{
  setlocale(LC_ALL, "");
  parse_args(argc, argv);

  if (mask == NULL)
    mask = g_string_new("pd"); /* Default. */

  g_printerr("[%s] mask=%s, type=%d\n", __func__, mask->str, type);

  g_assert(q == NULL);
  q = quvi_new();
  exit_if_error();

  while (quvi_script_next(q, type) == QUVI_TRUE)
    dump_script(q);

  g_string_free(mask, TRUE);
  cleanup();

  g_assert(q == NULL);

  return (0);
}

/* vim: set ts=2 sw=2 tw=72 expandtab: */
