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
@return New handle, @ref quvi_playlist_free it when done using it
@note Use @ref quvi_ok for checking if an error occurred
@sa @ref parse_playlist
@ingroup playlistprop
*/
quvi_playlist_t quvi_playlist_new(quvi_t handle, const char *url)
{
  _quvi_playlist_t qp;
  _quvi_t q;

  /* If G_DISABLE_CHECKS is defined then the check is not performed. */
  g_return_val_if_fail(handle != NULL, NULL);
  g_return_val_if_fail(url != NULL, NULL);

  q = (_quvi_t) handle;
  qp = NULL;

  q->status.rc = m_match_playlist_script(q, &qp, url, QM_MATCH_PS_PARSE);
  return (qp);
}

/* vim: set ts=2 sw=2 tw=72 expandtab: */
