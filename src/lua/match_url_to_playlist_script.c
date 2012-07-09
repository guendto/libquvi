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

#include "quvi.h"
/* -- */
#include "_quvi_s.h"
#include "_quvi_playlist_s.h"
/* -- */
#include "lua/exec.h"

QuviError l_match_url_to_playlist_script(_quvi_playlist_t m, GSList **curr)
{
  *curr = m->handle.quvi->scripts.playlist;
  while (*curr != NULL)
    {
      const QuviError rc = l_exec_playlist_script_ident(m, *curr);

      if (rc == QUVI_OK)
        return (rc);

      *curr = g_slist_next(*curr);
    }
  return (QUVI_ERROR_NO_SUPPORT);
}

/* vim: set ts=2 sw=2 tw=72 expandtab: */
