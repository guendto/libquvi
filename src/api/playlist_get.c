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

/** @file playlist_get.c */

#include "config.h"

#include <glib.h>

#include "quvi.h"
/* -- */
#include "_quvi_s.h"
#include "_quvi_playlist_s.h"

static QuviError _playlist_get(_quvi_playlist_t p,
                               QuviPlaylistProperty n, ...)
{
  QuviError rc;
  gdouble *dp;
  va_list arg;
  gchar **sp;
  glong *lp;
  gint type;

  va_start(arg, n);
  type = QUVI_PLAYLIST_PROPERTY_TYPE_MASK & (gint) n;

  dp = NULL;
  sp = NULL;
  lp = NULL;

  rc = QUVI_OK;

  switch (type)
    {
    case QUVI_PLAYLIST_PROPERTY_TYPE_STRING:
      sp = va_arg(arg, gchar**);
      if (sp == NULL)
        rc = QUVI_ERROR_INVALID_ARG;
      break;
    case QUVI_PLAYLIST_PROPERTY_TYPE_LONG:
      lp = va_arg(arg, glong*);
      if (lp == NULL)
        rc = QUVI_ERROR_INVALID_ARG;
      break;
    case QUVI_PLAYLIST_PROPERTY_TYPE_DOUBLE:
      dp = va_arg(arg, gdouble*);
      if (dp == NULL)
        rc = QUVI_ERROR_INVALID_ARG;
      break;
    default:
      rc = QUVI_ERROR_INVALID_ARG;
      break;
    }
  va_end(arg);

  if (rc != QUVI_OK)
    return (rc);

  switch (n)
    {
    case QUVI_PLAYLIST_PROPERTY_ID:
      *sp = p->id.playlist->str;
      break;
    case QUVI_PLAYLIST_PROPERTY_MEDIA_URL:
      *sp = (gchar*) p->url.curr.media->data;
      break;
    default:
      rc = QUVI_ERROR_INVALID_ARG;
      break;
    }
  return (rc);
}

/** @brief Return a playlist property
@sa @ref parse_playlist
@ingroup playlistprop
*/
void quvi_playlist_get(quvi_playlist_t handle,
                       QuviPlaylistProperty property, ...)
{
  _quvi_playlist_t pl;
  va_list arg;
  gpointer p;
  _quvi_t q;

  /* If G_DISABLE_CHECKS is defined then the check is not performed. */
  g_return_if_fail(handle != NULL);

  va_start(arg, property);
  p = va_arg(arg, gpointer);
  va_end(arg);

  pl = (_quvi_playlist_t) handle;
  q = pl->handle.quvi;

  q->status.rc = _playlist_get(pl, property, p);
}

/* vim: set ts=2 sw=2 tw=72 expandtab: */
