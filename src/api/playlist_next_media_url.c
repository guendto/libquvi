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

/** @file playlist_next_media_url.c */

#include "config.h"

#include <glib.h>

#include "quvi.h"
/* -- */
#include "_quvi_s.h"
#include "_quvi_playlist_s.h"

/** @brief Traverse to next playlist media URL
@return QUVI_TRUE if succeeded, otherwise QUVI_FALSE
@sa @ref parse_playlist
@ingroup playlistprop
*/
QuviBoolean quvi_playlist_next_media_url(quvi_playlist_t handle)
{
  _quvi_playlist_t qp = (_quvi_playlist_t) handle;

  /* If G_DISABLE_CHECKS is defined then the check is not performed. */
  g_return_val_if_fail(handle != NULL, QUVI_FALSE);

  qp->url.curr.media = (qp->url.curr.media != NULL)
                       ? g_slist_next(qp->url.curr.media)
                       : qp->url.media;

  return ((qp->url.curr.media != NULL)
          ? QUVI_TRUE
          : QUVI_FALSE);
}

/* vim: set ts=2 sw=2 tw=72 expandtab: */
