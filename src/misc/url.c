/* libquvi
 * Copyright (C) 2013  Toni Gundogdu <legatvs@gmail.com>
 *
 * This file is part of libquvi <http://quvi.sourceforge.net/>.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as
 * published by the Free Software Foundation, either version 3 of the
 * License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public
 * License along with this program.  If not, see
 * <http://www.gnu.org/licenses/>.
 */

#include "config.h"

#include <glib.h>
/* -- */
#include "misc/url.h"

static gboolean _is_unescaped(const gchar *s)
{
  gboolean r;
  gchar *u;
  u = g_uri_unescape_string(s, NULL);
  r = g_strcmp0(u,s) == 0 ? TRUE:FALSE;
  g_free(u);
  return (r);
}

gchar *m_url_unescaped_form(const gchar *s)
{
  gchar *r = g_strdup(s);
  do
    {
      gchar *u = g_uri_unescape_string(r, NULL);
      if (u == NULL)
        break;
      g_free(r);
      r = u;
    }
  while (_is_unescaped(r) == FALSE);
  return (r);
}

gchar *m_url_escaped_form(const gchar *s)
{
  static const gchar *reserved_chars = "!*'();:@&=+$,/?#[]";
  gchar *u, *r;
  u = m_url_unescaped_form(s);
  r = g_uri_escape_string(u, reserved_chars, FALSE);
  g_free(u);
  return (r);
}

/* vim: set ts=2 sw=2 tw=72 expandtab: */
