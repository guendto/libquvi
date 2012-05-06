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

/** @file playlist_new.c */

#include "config.h"

#include <glib.h>

#include "quvi.h"
/* -- */
#include "_quvi_s.h"
#include "_quvi_playlist_s.h"
/* -- */
#include "misc/match_playlist_script.h"

/** @brief Parse playlist properties for URL
@note @ref quvi_playlist_free the handle when done using it
@sa @ref parse_playlist
@ingroup playlistprop
*/
quvi_playlist_t quvi_playlist_new(quvi_t handle, char *url)
{
  _quvi_t q = (_quvi_t) handle;
  _quvi_playlist_t p = NULL;

  /* If G_DISABLE_CHECKS is defined then the check is not performed. */
  g_return_val_if_fail(handle != NULL, NULL);
  g_return_val_if_fail(url != NULL, NULL);

  q->status.rc = m_match_playlist_script(q, &p, (const gchar*) url,
                                         QM_MATCH_PS_PARSE, NULL);
  return (p);
}

/* vim: set ts=2 sw=2 tw=72 expandtab: */
