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
#include "misc/playlist.h"

gpointer m_playlist_new(_quvi_t q, const gchar *url)
{
  _quvi_playlist_t qp = g_new0(struct _quvi_playlist_s, 1);
  /* URL */
  qp->url.input = g_string_new(url);
  /* ID */
  qp->id.playlist = g_string_new(NULL);
  /* Handle */
  qp->handle.quvi = q;
  return (qp);
}

static void _url_free(gpointer p, gpointer userdata)
{
  if (p == NULL)
    return;

  g_free(p);
  p = NULL;
}

void m_playlist_free(_quvi_playlist_t qp)
{
  if (qp == NULL)
    return;

  /* URLs */

#ifdef HAVE_GLIB_2_28
  g_slist_free_full(qp->url.media, _url_free);
#else
  g_slist_foreach(qp->url.media, _url_free, NULL);
  g_slist_free(qp->url.media);
#endif
  qp->url.media = NULL;

  g_string_free(qp->url.input, TRUE);
  qp->url.input = NULL;

  /* ID */

  g_string_free(qp->id.playlist, TRUE);
  qp->id.playlist = NULL;

  g_free(qp);
  qp = NULL;
}

/* vim: set ts=2 sw=2 tw=72 expandtab: */
