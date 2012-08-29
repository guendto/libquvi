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

glong qerr(quvi_t q)
{
  glong n;
  quvi_get(q, QUVI_INFO_ERROR_CODE, &n);
  return (n);
}

glong qerr_m(quvi_t q, const gchar *url)
{
  glong n = qerr(q);
  g_test_message("url=%s", url);
  g_test_message("errmsg=%s", quvi_errmsg(q));
  return (n);
}

/* vim: set ts=2 sw=2 tw=72 expandtab: */
