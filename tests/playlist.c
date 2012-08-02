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

#include <string.h>
#include <glib.h>
#include <quvi.h>

#include "tests.h"

static void test_playlist()
{
  static const gchar URL[] =
    "http://soundcloud.com/thelittleidiot/sets/destroyed/";

  quvi_playlist_t qp;
  quvi_t q;
  gchar *s;

  if (chk_internet() == FALSE)
    return;

  if (chk_skip(__func__) == TRUE)
    return;

  q = quvi_new();
  g_assert(q != NULL);
  g_assert_cmpint(qerr(q), ==, QUVI_OK);

  chk_verbose(q);

  qp = quvi_playlist_new(q, URL);
  g_assert_cmpint(qerr(q), ==, QUVI_OK);
  g_assert(qp != NULL);

  quvi_playlist_get(qp, QUVI_PLAYLIST_PROPERTY_ID-1, &s);
  g_assert_cmpint(qerr(q), ==, QUVI_ERROR_INVALID_ARG);

  quvi_playlist_get(qp, QUVI_PLAYLIST_MEDIA_PROPERTY_URL+1, &s);
  g_assert_cmpint(qerr(q), ==, QUVI_ERROR_INVALID_ARG);

  quvi_playlist_get(qp, QUVI_PLAYLIST_PROPERTY_ID, &s);
  g_assert_cmpint(qerr(q), ==, QUVI_OK);
  g_assert_cmpstr(s, ==, "thelittleidiot_destroyed");

  {
    gint i = 0;
    while (quvi_playlist_media_next(qp) == QUVI_TRUE)
      {
        quvi_playlist_get(qp, QUVI_PLAYLIST_MEDIA_PROPERTY_URL, &s);
        g_assert_cmpint(qerr(q), ==, QUVI_OK);
        g_assert_cmpint(strlen(s), >, 0);
        ++i;
      }
    g_assert_cmpint(i, >, 1);
  }

  quvi_playlist_free(qp);
  quvi_free(q);
}

static void test_playlist_short()
{
  static const gchar URL[] = "http://is.gd/BjbpVn";

  quvi_playlist_t qp;
  quvi_t q;
  gchar *s;

  if (chk_internet() == FALSE)
    return;

  if (chk_skip(__func__) == TRUE)
    return;

  q = quvi_new();
  g_assert(q != NULL);
  g_assert_cmpint(qerr(q), ==, QUVI_OK);

  chk_verbose(q);

  qp = quvi_playlist_new(q, URL);
  g_assert_cmpint(qerr(q), ==, QUVI_OK);
  g_assert(qp != NULL);

  quvi_playlist_get(qp, QUVI_PLAYLIST_PROPERTY_ID, &s);
  g_assert_cmpint(qerr(q), ==, QUVI_OK);
  g_assert_cmpstr(s, ==, "thelittleidiot_destroyed");

  {
    gint i = 0;
    while (quvi_playlist_media_next(qp) == QUVI_TRUE)
      {
        quvi_playlist_get(qp, QUVI_PLAYLIST_MEDIA_PROPERTY_URL, &s);
        g_assert_cmpint(qerr(q), ==, QUVI_OK);
        g_assert_cmpint(strlen(s), >, 0);
        ++i;
      }
    g_assert_cmpint(i, >, 1);
  }

  quvi_playlist_free(qp);
  quvi_free(q);
}

static void test_playlist_nosupport()
{
  static const gchar URL[] = "http://example.com/";

  quvi_playlist_t qp;
  quvi_t q;
  gchar *s;

  if (chk_internet() == FALSE)
    return;

  if (chk_skip(__func__) == TRUE)
    return;

  q = quvi_new();
  g_assert(q != NULL);
  g_assert_cmpint(qerr(q), ==, QUVI_OK);

  chk_verbose(q);

  qp = quvi_playlist_new(q, URL);
  g_assert_cmpint(qerr(q), ==, QUVI_ERROR_NO_SUPPORT);
  g_assert(qp != NULL);

  quvi_playlist_get(qp, QUVI_PLAYLIST_PROPERTY_ID, &s);
  g_assert_cmpint(qerr(q), ==, QUVI_OK);
  g_assert_cmpstr(s, ==, "");

  quvi_playlist_free(qp);
  quvi_free(q);
}

gint main(gint argc, gchar **argv)
{
  g_test_init(&argc, &argv, NULL);
  g_test_add_func("/quvi/playlist", test_playlist);
  g_test_add_func("/quvi/playlist (short)", test_playlist_short);
  g_test_add_func("/quvi/playlist (nosupport)", test_playlist_nosupport);
  return (g_test_run());
}

/* vim: set ts=2 sw=2 tw=72 expandtab: */
