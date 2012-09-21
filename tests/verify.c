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

#include <string.h>
#include <glib.h>
#include <quvi.h>

#include "tests.h"

#define chk_len(p)\
  do {\
    gchar *s = NULL;\
    quvi_verify_get(qv, p, &s);\
    g_assert(s != NULL);\
    g_test_message("%s=%s", #p, s);\
    g_assert_cmpint(strlen(s), >, 1);\
  } while (0)

#define chk_val(p)\
  do {\
    gdouble n = 0;\
    quvi_verify_get(qv, p, &n);\
    g_test_message("%s=%f", #p, n);\
    g_assert_cmpfloat(n, >, 0);\
  } while (0)

static void test_verify()
{
  static const gchar URL[] = "http://is.gd/SKyg8m";

  quvi_verify_t qv;
  quvi_t q;
  gchar *v;

  if (chk_internet() == FALSE)
    return;

  if (chk_skip(__func__) == TRUE)
    return;

  q = quvi_new();
  g_assert(q != NULL);
  g_assert_cmpint(qerr(q), ==, QUVI_OK);

  chk_verbose(q);

  qv = quvi_verify_new(q, URL);
  g_assert_cmpint(qerr_m(q, URL), ==, QUVI_OK);
  g_assert(qv != NULL);

  quvi_verify_get(qv, QUVI_VERIFY_PROPERTY_FILE_EXTENSION-1, &v);
  g_assert_cmpint(qerr(q), ==, QUVI_ERROR_INVALID_ARG);

  quvi_verify_get(qv, QUVI_VERIFY_PROPERTY_LENGTH_BYTES+1, &v);
  g_assert_cmpint(qerr(q), ==, QUVI_ERROR_INVALID_ARG);

  chk_len(QUVI_VERIFY_PROPERTY_FILE_EXTENSION);
  chk_len(QUVI_VERIFY_PROPERTY_CONTENT_TYPE);

  chk_val(QUVI_VERIFY_PROPERTY_LENGTH_BYTES);

  quvi_verify_free(qv);
  quvi_free(q);
}

gint main(gint argc, gchar **argv)
{
  g_test_init(&argc, &argv, NULL);
  g_test_add_func("/quvi/verify", test_verify);
  return (g_test_run());
}

/* vim: set ts=2 sw=2 tw=72 expandtab: */
