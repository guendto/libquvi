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

#include <glib.h>
#include <quvi.h>

#include "tests.h"

static void test_resolve_core()
{
  static const gchar URL[] = "http://is.gd/9lrXf8";

  static const gchar DST[] =
    "http://www.collegehumor.com/video/6781885/batman-blows-his-cover";

  quvi_resolve_t qr;
  quvi_t q;

  if (chk_internet() == FALSE)
    return;

  if (chk_skip(__func__) == TRUE)
    return;

  q = quvi_new();
  g_assert(q != NULL);
  g_assert_cmpint(qerr(q), ==, QUVI_OK);

  chk_verbose(q);

  qr = quvi_resolve_new(q, URL);
  g_assert_cmpint(qerr_m(q, URL), ==, QUVI_OK);
  g_assert(qr != NULL);

  g_assert(quvi_resolve_forwarded(qr) == QUVI_TRUE);
  g_assert_cmpstr(quvi_resolve_destination_url(qr), ==, DST);

  quvi_resolve_free(qr);
  quvi_free(q);
}

static void test_resolve_3()
{
  static const gchar URL[] = "http://is.gd/gQ4pYW";

  static const gchar DST[] =
    "http://www.thefirearmblog.com/blog/2012/06/11/shooting-drones/"
    "?utm_source=feedburner&utm_medium=feed&utm_campaign="
    "Feed%3A+TheFirearmBlog+%28The+Firearm+Blog%29";

  quvi_resolve_t qr;
  quvi_t q;

  if (chk_internet() == FALSE)
    return;

  if (chk_skip(__func__) == TRUE)
    return;

  q = quvi_new();
  g_assert(q != NULL);
  g_assert_cmpint(qerr(q), ==, QUVI_OK);

  chk_verbose(q);

  qr = quvi_resolve_new(q, URL);
  g_assert_cmpint(qerr_m(q, URL), ==, QUVI_OK);
  g_assert(qr != NULL);

  g_assert(quvi_resolve_forwarded(qr) == QUVI_TRUE);
  g_assert_cmpstr(quvi_resolve_destination_url(qr), ==, DST);

  quvi_resolve_free(qr);
  quvi_free(q);
}

static void test_resolve_nodst()
{
  static const gchar URL[] = "http://www.iana.org/domains/example/";

  quvi_resolve_t qr;
  quvi_t q;

  if (chk_internet() == FALSE)
    return;

  if (chk_skip(__func__) == TRUE)
    return;

  q = quvi_new();
  g_assert(q != NULL);
  g_assert_cmpint(qerr(q), ==, QUVI_OK);

  chk_verbose(q);

  qr = quvi_resolve_new(q, URL);
  g_assert_cmpint(qerr_m(q, URL), ==, QUVI_OK);
  g_assert(qr != NULL);

  g_assert_cmpint(quvi_resolve_forwarded(qr), ==, QUVI_FALSE);

  quvi_resolve_free(qr);
  quvi_free(q);
}

static void test_resolve_nodst_t_param()
{
  static const gchar URL[] =
    "http://www.youtube.com/watch?v=G4evlxq34og#t=3m20";

  quvi_resolve_t qr;
  quvi_t q;

  if (chk_internet() == FALSE)
    return;

  if (chk_skip(__func__) == TRUE)
    return;

  q = quvi_new();
  g_assert(q != NULL);
  g_assert_cmpint(qerr(q), ==, QUVI_OK);

  chk_verbose(q);

  qr = quvi_resolve_new(q, URL);
  g_assert_cmpint(qerr_m(q, URL), ==, QUVI_OK);
  g_assert(qr != NULL);

  /* g00gle servers redirect to the media URL stripping the #t
   * parameter.  The library should not be fooled by this trickery. */
  g_assert_cmpint(quvi_resolve_forwarded(qr), ==, QUVI_FALSE);

  quvi_resolve_free(qr);
  quvi_free(q);
}

/* Known limitation: Shortened Y0uTube media URLs with the #t parameter
 * do not work with the library. The test below should redirect to
 * "http://www.youtube.com/watch?v=G4evlxq34og", missing the #t
 * parameter, see the above example for the explanation. */
static void test_resolve_shortened_with_t_param()
{
  static const gchar URL[] = "http://is.gd/TRWtNf";
  /* http://www.youtube.com/watch?v=G4evlxq34og#t=3m20 */

  static const gchar DST[] =
    "http://www.youtube.com/watch?v=G4evlxq34og";

  quvi_resolve_t qr;
  quvi_t q;

  if (chk_internet() == FALSE)
    return;

  if (chk_skip(__func__) == TRUE)
    return;

  q = quvi_new();
  g_assert(q != NULL);
  g_assert_cmpint(qerr(q), ==, QUVI_OK);

  chk_verbose(q);

  qr = quvi_resolve_new(q, URL);
  g_assert_cmpint(qerr_m(q, URL), ==, QUVI_OK);
  g_assert(qr != NULL);

  g_assert_cmpint(quvi_resolve_forwarded(qr), ==, QUVI_TRUE);
  g_assert_cmpstr(quvi_resolve_destination_url(qr), ==, DST);

  quvi_resolve_free(qr);
  quvi_free(q);
}

gint main(gint argc, gchar **argv)
{
  g_test_init(&argc, &argv, NULL);
  g_test_add_func("/quvi/resolve (core)", test_resolve_core);
  g_test_add_func("/quvi/resolve (3)", test_resolve_3);
  g_test_add_func("/quvi/resolve (nodst)", test_resolve_nodst);
  g_test_add_func("/quvi/resolve (nodst #t param)",
                  test_resolve_nodst_t_param);
  g_test_add_func("/quvi/resolve (short URL with #t param)",
                  test_resolve_shortened_with_t_param);
  return (g_test_run());
}

/* vim: set ts=2 sw=2 tw=72 expandtab: */
