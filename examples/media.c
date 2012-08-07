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

#include "config.h"

#include <locale.h>
#include <stdlib.h>
#include <string.h>
#include <glib.h>
#include <quvi.h>

#include "examples.h"

static void usage()
{
  g_printerr("Usage: media [-f<fmt_id,...>] [-v] [-b] [-a] <URL>\n"
             "Options:\n"
             "  -f<arg>   Select arg format ID from the available streams,\n"
             "             this may also be a comma-separated list of IDs\n"
             "  -v        Enable verbose output (libcurl)\n"
             "  -b        Choose the best quality stream\n"
             "  -a        Enable autoproxy feature\n");
  exit(0);
}

static void dump_stream()
{
  gchar *fmt_id, *url;

  quvi_media_get(qm, QUVI_MEDIA_STREAM_PROPERTY_FORMAT_ID, &fmt_id);
  quvi_media_get(qm, QUVI_MEDIA_STREAM_PROPERTY_URL, &url);

  g_print("[%s] fmt_id='%s', url='%s'\n", __func__, fmt_id, url);
}

static void dump_streams()
{
  while (quvi_media_stream_next(qm) == QUVI_TRUE)
    dump_stream();
}

typedef quvi_callback_status qcs;

gint main(gint argc, gchar **argv)
{
  gboolean best_flag = FALSE;
  gchar *fmt_id = NULL;
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
      else if (g_strcmp0("-h", argv[i]) == 0)
        usage();
      else if (g_strcmp0("-a", argv[i]) == 0)
        enable_autoproxy();
      else if (g_strcmp0("-b", argv[i]) == 0)
        best_flag = TRUE;
      else if (g_str_has_prefix(argv[i], "-f") == TRUE)
        {
          if (strlen(argv[i]) >2)
            fmt_id = &argv[i][2];
          else
            g_printerr("[%s] `-f' ignored, specify format ID\n", __func__);
        }
      else
        url = argv[i];
    }

  if (url == NULL)
    usage();

  quvi_set(q, QUVI_OPTION_CALLBACK_STATUS, (qcs) status);

  qm = quvi_media_new(q, url);
  exit_if_error();
  {
    gchar *s;

    quvi_media_get(qm, QUVI_MEDIA_PROPERTY_TITLE, &s);
    g_print("[%s] title='%s'\n", __func__, s);

    if (best_flag == TRUE)
      {
        quvi_media_stream_choose_best(qm);
        dump_stream();
      }
    else if (fmt_id != NULL)
      {
        quvi_media_stream_select(qm, fmt_id);
        exit_if_error();
        dump_stream();
      }
    else
      dump_streams();
  }
  cleanup();

  g_assert(qm == NULL);
  g_assert(q == NULL);

  return (0);
}

/* vim: set ts=2 sw=2 tw=72 expandtab: */
