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

static gchar *URLs[] =
{
  "http://www.gaskrank.tv/tv/motorrad-oldtimer/1928-henderson-deluxe-alt-und--19115.htm",
  "http://www.gaskrank.tv/tv/motorrad-oldtimer/1912-harley-davidson-superscho-9481.htm",
  NULL
};

static gchar *TITLEs[] =
{
  "1928 Henderson Deluxe - alt und mit der Patina des Alters aber läuft",
  "1912 Harley Davidson - superschön restauriert",
  NULL
};

#define chk_len(p) \
  do {\
    gchar *s = NULL; \
    quvi_media_get(qm, p, &s); \
    g_assert(s != NULL); \
    g_test_message("%s=%s", #p, s); \
    g_assert_cmpint(strlen(s), >, 1); \
  } while (0)

#define chk_val(p) \
  do {\
    gdouble n = -1; \
    quvi_media_get(qm, p, &n); \
    g_test_message("%s=%f", #p, n); \
    g_assert_cmpfloat(n, >, -1);\
  } while (0)

static void test_media()
{
  quvi_media_t qm;
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

  qm = quvi_media_new(q, URLs[0]);
  g_assert_cmpint(qerr(q), ==, QUVI_OK);
  g_assert(qm != NULL);

  quvi_media_get(qm, QUVI_MEDIA_PROPERTY_FILE_EXTENSION-1, &s);
  g_assert_cmpint(qerr(q), ==, QUVI_ERROR_INVALID_ARG);

  quvi_media_get(qm, QUVI_MEDIA_PROPERTY_DURATION_MS+1, &s);
  g_assert_cmpint(qerr(q), ==, QUVI_ERROR_INVALID_ARG);

  /* string */
  chk_len(QUVI_MEDIA_PROPERTY_FILE_EXTENSION);
  chk_len(QUVI_MEDIA_PROPERTY_THUMBNAIL_URL);
  chk_len(QUVI_MEDIA_PROPERTY_CONTENT_TYPE);
  chk_len(QUVI_MEDIA_PROPERTY_STREAM_URL);
  chk_len(QUVI_MEDIA_PROPERTY_TITLE);
  chk_len(QUVI_MEDIA_PROPERTY_ID);

  /* double */
  chk_val(QUVI_MEDIA_PROPERTY_LENGTH_BYTES);
  chk_val(QUVI_MEDIA_PROPERTY_START_TIME_MS);
  chk_val(QUVI_MEDIA_PROPERTY_DURATION_MS);

  quvi_media_free(qm);
  quvi_free(q);
}

static void test_media_short()
{
  static const gchar URL[] = "http://tinyurl.com/d8s3y54";

  quvi_media_t qm;
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

  qm = quvi_media_new(q, URL);
  g_assert_cmpint(qerr(q), ==, QUVI_OK);
  g_assert(qm != NULL);

  quvi_media_get(qm, QUVI_MEDIA_PROPERTY_TITLE, &s);
  g_assert_cmpint(qerr(q), ==, QUVI_OK);
  g_assert_cmpstr(s, ==, TITLEs[1]);

  quvi_media_free(qm);
  quvi_free(q);
}

static void test_media_starttime()
{
  static const gchar *URL =
    "http://www.youtube.com/watch?v=LWxTGJ3TK1U#t=2m22s";

  quvi_media_t qm;
  gdouble st = 0;
  quvi_t q;

  if (chk_internet() == FALSE)
    return;

  if (chk_skip(__func__) == TRUE)
    return;

  q = quvi_new();
  g_assert(q != NULL);
  g_assert_cmpint(qerr(q), ==, QUVI_OK);

  chk_verbose(q);

  qm = quvi_media_new(q, URL);
  g_assert_cmpint(qerr(q), ==, QUVI_OK);
  g_assert(qm != NULL);

  quvi_media_get(qm, QUVI_MEDIA_PROPERTY_START_TIME_MS, &st);
  g_assert_cmpint(qerr(q), ==, QUVI_OK);
  g_assert_cmpint(st, ==, 142000);

  quvi_media_free(qm);
  quvi_free(q);
}

static void test_media_nosupport()
{
  static const gchar URL[] = "http://example.com";

  quvi_media_t qm;
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

  qm = quvi_media_new(q, URL);
  g_assert_cmpint(qerr(q), ==, QUVI_ERROR_NO_SUPPORT);
  g_assert(qm != NULL);

  quvi_media_get(qm, QUVI_MEDIA_PROPERTY_TITLE, &s);
  g_assert_cmpint(qerr(q), ==, QUVI_OK);
  g_assert_cmpstr(s, ==, "");

  quvi_media_free(qm);
  quvi_free(q);
}

static void test_media_same_q()
{
  quvi_media_t qm;
  gint i = 0;
  quvi_t q;

  if (chk_internet() == FALSE)
    return;

  if (chk_skip(__func__) == TRUE)
    return;

  q = quvi_new();
  g_assert(q != NULL);
  g_assert_cmpint(qerr(q), ==, QUVI_OK);

  chk_verbose(q);

  for (; URLs[i] != NULL; ++i)
    {
      gchar *s = NULL;

      qm = quvi_media_new(q, URLs[i]);
      g_assert_cmpint(qerr(q), ==, QUVI_OK);
      g_assert(qm != NULL);

      quvi_media_get(qm, QUVI_MEDIA_PROPERTY_TITLE, &s);
      g_assert_cmpint(qerr(q), ==, QUVI_OK);
      g_assert_cmpstr(s, ==, TITLEs[i]);

      quvi_media_free(qm);
    }
  quvi_free(q);
}

gint main(gint argc, gchar **argv)
{
  g_test_init(&argc, &argv, NULL);
  g_test_add_func("/quvi/media", test_media);
  g_test_add_func("/quvi/media (short)", test_media_short);
  g_test_add_func("/quvi/media (nosupport)", test_media_nosupport);
  g_test_add_func("/quvi/media (start_time)", test_media_starttime);
  g_test_add_func("/quvi/media (same handle)", test_media_same_q);
  return (g_test_run());
}

/* vim: set ts=2 sw=2 tw=72 expandtab: */
