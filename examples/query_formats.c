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

#include <locale.h>
#include <stdlib.h>
#include <glib.h>
#include <quvi.h>
#include <curl/curl.h>

static void usage()
{
  g_printerr("Usage: query_formats <URL>\n");
  exit(0);
}

extern QuviError status(glong, gpointer);
extern void exit_if_error();
extern void cleanup();

typedef quvi_callback_status qcs;

extern quvi_query_formats_t qqf;
extern quvi_t q;

static void enable_verbose()
{
  CURL *c = NULL;
  g_assert(q != NULL);
  quvi_get(q, QUVI_INFO_CURL_HANDLE, &c);
  g_assert(c != NULL);
  curl_easy_setopt(c, CURLOPT_VERBOSE, 1L);
}

gint main(gint argc, gchar **argv)
{
  gchar *url = NULL;
  gint i = 1;

  g_assert(qqf == NULL);
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

  if (url == NULL)
    usage();

  quvi_set(q, QUVI_OPTION_CALLBACK_STATUS, (qcs) status);

  qqf = quvi_query_formats_new(q, url);
  exit_if_error();
  {
    const gchar *s = NULL;
    while ((s = quvi_query_formats_next_format(qqf)) != NULL)
      g_print("%s\n", s);
  }
  cleanup();

  g_assert(qqf == NULL);
  g_assert(q == NULL);

  return (0);
}

/* vim: set ts=2 sw=2 tw=72 expandtab: */
