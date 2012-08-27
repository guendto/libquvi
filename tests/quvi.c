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

#include <stdlib.h>
#include <glib.h>
#include <quvi.h>

#include "tests.h"

static void test_quvi()
{
  gpointer p;
  quvi_t q;
  gint n;

  if (chk_skip(__func__) == TRUE)
    return;

  q = quvi_new();
  g_assert(q != NULL);
  g_assert_cmpint(qerr(q), ==, QUVI_OK);

  g_assert_cmpstr(quvi_errmsg(q), ==, "No error");

  /* quvi_get */

  quvi_get(q, QUVI_INFO_RESPONSE_CODE-1, &n);
  g_assert_cmpint(n, ==, 0);

  quvi_get(q, QUVI_INFO_RESPONSE_CODE-1, &p);
  g_assert(p == NULL);

  quvi_get(q, QUVI_INFO_ERROR_CODE+1, &n);
  g_assert_cmpint(n, ==, 0);

  quvi_get(q, QUVI_INFO_ERROR_CODE+1, &p);
  g_assert(p == NULL);

  quvi_get(q, QUVI_INFO_CURL_HANDLE, &p);
  g_assert(p != NULL);
  p = NULL;

  quvi_get(q, QUVI_INFO_CURL_HANDLE+1, &p);
  g_assert(p == NULL);

  /* quvi_set */

  quvi_set(q, QUVI_OPTION_MEDIA_SCRIPT_PROTOCOL_CATEGORY-1, 0);
  g_assert_cmpint(qerr(q), ==, QUVI_ERROR_INVALID_ARG);

  quvi_set(q, QUVI_OPTION_AUTOPROXY+1, 0);
  g_assert_cmpint(qerr(q), ==, QUVI_ERROR_INVALID_ARG);

  quvi_free(q);
}

static void test_version()
{
  if (chk_skip(__func__) == TRUE)
    return;

  if (g_test_trap_fork(0,
                       G_TEST_TRAP_SILENCE_STDOUT|G_TEST_TRAP_SILENCE_STDERR))
    {
      g_print("%s", quvi_version(QUVI_VERSION));
      g_printerr("%s", quvi_version(QUVI_VERSION_SCRIPTS));
      exit(0);
    }
  g_test_trap_assert_passed();
  g_test_trap_assert_stdout("v?.?.?*");
  g_test_trap_assert_stderr("v?.?*");

  g_assert_cmpstr(quvi_version(QUVI_VERSION_SCRIPTS+1),
                  ==, quvi_version(QUVI_VERSION));

  g_assert_cmpstr(quvi_version(QUVI_VERSION-1),
                  ==, quvi_version(QUVI_VERSION));
}

gint main(gint argc, gchar **argv)
{
  g_test_init(&argc, &argv, NULL);
  g_test_add_func("/quvi", test_quvi);
  g_test_add_func("/quvi/version", test_version);
  return (g_test_run());
}

/* vim: set ts=2 sw=2 tw=72 expandtab: */
