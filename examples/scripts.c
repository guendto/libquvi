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

#include <glib.h>
#include <quvi.h>

extern void exit_if_error();
extern void cleanup();

static QuviScriptType t = QUVI_SCRIPT_TYPE_MEDIA;

quvi_media_t qm = NULL;
quvi_t q = NULL;

int main(int argc, char **argv)
{
  q = quvi_new();
  exit_if_error();

  if (argc >2)
    {
      if (argv[1][0] == '-')
        {
          switch (argv[1][1])
            {
            case 'p':
              t = QUVI_SCRIPT_TYPE_PLAYLIST;
              break;
            case 'm':
            default:
              t = QUVI_SCRIPT_TYPE_MEDIA;
              break;
            case 's':
              t = QUVI_SCRIPT_TYPE_SCAN;
              break;
            }
        }
    }

  while (quvi_script_next(q, t) == QUVI_TRUE)
    {
      gchar *s = NULL;
      quvi_script_get(q, t, QUVI_SCRIPT_PROPERTY_DOMAIN, &s);
      g_print("%s\n", s);
    }

  cleanup();

  return (0);
}

/* vim: set ts=2 sw=2 tw=72 expandtab: */
