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
#include <string.h>

gchar *to_utf8(const gchar *s, const gchar *from)
{
  if (!g_utf8_validate(s, -1, NULL))
    {
      gchar *c = g_locale_to_utf8(s, -1, NULL, NULL, NULL);
      if (c != NULL)
        return (c);
      else
        {
          if (from != NULL && strlen(from) >0)
            {
              return (g_convert_with_fallback(s, -1, "UTF-8", from,
                                              NULL, NULL, NULL, NULL));
            }
        }
    }
  return (NULL);
}

/* vim: set ts=2 sw=2 tw=72 expandtab: */
