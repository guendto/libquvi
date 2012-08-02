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

#include "examples.h"

static void usage()
{
  g_printerr("Usage: playlist <URL>\n");
  exit(0);
}

typedef quvi_callback_status qcs;

gint main(gint argc, gchar **argv)
{
  gchar *url = NULL;
  gint i = 1;

  g_assert(qp == NULL);
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
      else if (g_strcmp0("-a", argv[i]) == 0)
        enable_autoproxy();
      else
        url = argv[i];
    }

  if (url == NULL)
    usage();

  quvi_set(q, QUVI_OPTION_CALLBACK_STATUS, (qcs) status);

  qp = quvi_playlist_new(q, url);
  exit_if_error();
  {
    gchar *p_id, *m_url;
    gdouble m_dur_ms;

    quvi_playlist_get(qp, QUVI_PLAYLIST_PROPERTY_ID, &p_id);
    g_print("id=%s\n", p_id);

    while (quvi_playlist_media_next(qp) == QUVI_TRUE)
      {
        quvi_playlist_get(qp,
                          QUVI_PLAYLIST_MEDIA_PROPERTY_DURATION_MS, &m_dur_ms);

        quvi_playlist_get(qp, QUVI_PLAYLIST_MEDIA_PROPERTY_URL, &m_url);

        g_print("duration=%.0f, url=%s\n", m_dur_ms, m_url);
      }
  }

  cleanup();

  g_assert(qp == NULL);
  g_assert(q == NULL);

  return (0);
}

/* vim: set ts=2 sw=2 tw=72 expandtab: */
