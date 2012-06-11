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
#include <glib.h>
#include <quvi.h>
#include <curl/curl.h>

static void usage()
{
  g_printerr("Usage: media <URL>\n");
  exit(0);
}

extern QuviError status(glong, gpointer);
extern void exit_if_error();
extern void cleanup();

typedef quvi_callback_status qcs;

extern quvi_media_t qm;
extern quvi_t q;

static void enable_verbose()
{
  CURL *c;

  quvi_get(q, QUVI_INFO_CURL_HANDLE, &c);
  g_assert(c != NULL);

  curl_easy_setopt(c, CURLOPT_VERBOSE, 1L);
}

gint main(gint argc, gchar **argv)
{
  gchar *url = NULL;
  gint i = 1;

  g_assert(qm == NULL);
  g_assert(q == NULL);

  setlocale(LC_ALL, "");

  if (argc < 2)
    usage();

  q = quvi_new();
  exit_if_error();

  for (; i<argc; ++i)
    {
      if (g_strcmp0("-v", argv[i]) == 0)
        enable_verbose();
      else
        url = argv[i];
    }

  quvi_set(q, QUVI_OPTION_CALLBACK_STATUS, (qcs) status);

  qm = quvi_media_new(q, url);
  exit_if_error();
  {
    gchar *s = NULL;
    quvi_media_get(qm, QUVI_MEDIA_PROPERTY_TITLE, &s);
    g_print("%s\n", s);
  }
  cleanup();

  g_assert(qm == NULL);
  g_assert(q == NULL);

  return (0);
}

/* vim: set ts=2 sw=2 tw=72 expandtab: */
