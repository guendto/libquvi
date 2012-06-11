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

/* Check whether URL redirects to a new location. */

#include <locale.h>
#include <stdlib.h>
#include <glib.h>
#include <quvi.h>
#include <curl/curl.h>

extern QuviError status(glong, gpointer);
extern void exit_if_error();
extern void cleanup();

typedef quvi_callback_status qcs;

extern quvi_resolve_t qr;
extern quvi_t q;

static void enable_verbose()
{
  CURL *c = NULL;
  quvi_get(q, QUVI_INFO_CURL_HANDLE, &c);
  curl_easy_setopt(c, CURLOPT_VERBOSE, 1L);
}

static void help()
{
  g_print("Usage: resolve [-v] [URL]\n");
  cleanup();
  exit(0);
}

static const gchar *example_url = "http://is.gd/34YWaF";

gint main(gint argc, gchar **argv)
{
  gchar *url = NULL;
  gint i = 1;

  g_assert(qr == NULL);
  g_assert(q == NULL);

  setlocale(LC_ALL, "");

  q = quvi_new();
  exit_if_error();

  quvi_set(q, QUVI_OPTION_CALLBACK_STATUS, (qcs) status);

  for (; i<argc; ++i)
    {
      if (g_strcmp0("-v", argv[i]) == 0)
        enable_verbose();
      else if (g_strcmp0("-h", argv[i]) == 0)
        help();
      else
        url = argv[i];
    }

  if (url == NULL)
    {
      g_printerr("[%s] no input given: using example URL instead\n",
                 __func__);
      url = (gchar*) example_url;
    }

  g_printerr("[%s] url=%s\n", __func__, url);

  qr = quvi_resolve_new(q, url);
  exit_if_error();

  if (quvi_resolve_forwarded(qr) == QUVI_TRUE)
    {
      g_print("[%s] resolved=%s\n",
              __func__, quvi_resolve_destination_url(qr));
    }
  else
    g_print("[%s] no redirection\n", __func__);

  cleanup();

  g_assert(qr == NULL);
  g_assert(q == NULL);

  return (0);
}

/* vim: set ts=2 sw=2 tw=72 expandtab: */
