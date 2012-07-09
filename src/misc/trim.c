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

#include <glib.h>

/* -- */
#include "misc/re.h"

#define _W "libquvi: %s: %s"

gchar *m_trim(const gchar *s, const gchar *p, const gchar *w)
{
  GError *err;
  GRegex *re;
  gchar *r;

  err = NULL;
  re = g_regex_new(p, 0, 0, &err);

  if (err != NULL)
    {
      g_warning(_W, __func__, err->message);
      g_error_free(err);
      err = NULL;
      return (NULL);
    }

  r = g_regex_replace(re, s, -1, 0, w, 0, &err);
  if (err != NULL)
    {
      g_warning(_W, __func__, err->message);
      g_error_free(err);
      err = NULL;
      r = NULL;
    }

  g_regex_unref(re);
  re = NULL;

  return (r);
}

/* Trim null-terminated string of extra whitespace. */
gchar *m_trim_ws(const gchar *s)
{
  gchar *u, *t;

  u = NULL;
  t = m_trim(s, "^\\s*(.+?)\\s*$", "\\1");

  if (t != NULL)
    {
      u = m_trim(t, "\\s\\s+", " ");
      g_free(t);
      t = NULL;
    }
  return (u);
}

/* vim: set ts=2 sw=2 tw=72 expandtab: */
