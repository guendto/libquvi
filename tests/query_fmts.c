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

static const gchar URL[] = "http://www.youtube.com/watch?v=LWxTGJ3TK1U";

static void test_query_formats()
{
  quvi_query_formats_t qqf;
  quvi_t q;

  if (chk_internet() == FALSE)
    return;

  if (chk_skip(__func__) == TRUE)
    return;

  q = quvi_new();
  g_assert(q != NULL);
  g_assert_cmpint(qerr(q), ==, QUVI_OK);

  chk_verbose(q);

  qqf = quvi_query_formats_new(q, URL);
  g_assert_cmpint(qerr(q), ==, QUVI_OK);
  g_assert(qqf != NULL);
  {
    gchar **r = g_strsplit(quvi_query_formats_get(qqf), ",", 0);
    g_assert(r != NULL);
    g_assert_cmpint(g_strv_length(r), >, 1);
    g_strfreev(r);
    r = NULL;
  }
  quvi_query_formats_free(qqf);
  quvi_free(q);
}

gint main(gint argc, gchar **argv)
{
  g_test_init(&argc, &argv, NULL);
  g_test_add_func("/quvi/query formats", test_query_formats);
  return (g_test_run());
}

/* vim: set ts=2 sw=2 tw=72 expandtab: */
