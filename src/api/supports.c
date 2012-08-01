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

/** @file supports.c */

#include "config.h"

#include <glib.h>

#include "quvi.h"
/* -- */
#include "_quvi_s.h"
#include "_quvi_media_s.h"
#include "_quvi_playlist_s.h"
/* -- */
#include "misc/match_playlist_script.h"
#include "misc/match_media_script.h"

static QuviBoolean _supports_playlist(_quvi_t q, const gchar *url,
                                      const QuviSupportsMode mode)
{
  _quvi_playlist_t p = NULL;

  q->status.rc = m_match_playlist_script(q, &p, url,
                                         (mode == QUVI_SUPPORTS_MODE_OFFLINE)
                                         ? QM_MATCH_PS_SUPPORTED_OFFLINE
                                         : QM_MATCH_PS_SUPPORTED_ONLINE,
                                         NULL);
  if (p != NULL)
    {
      quvi_playlist_free((quvi_playlist_t) p);
      p = NULL;
    }
  return (quvi_ok(q));
}

static QuviBoolean _supports_media(_quvi_t q, const gchar *url,
                                   const QuviSupportsMode mode)
{
  _quvi_media_t qm = NULL;

  q->status.rc = m_match_media_script(q, &qm, url,
                                      (mode == QUVI_SUPPORTS_MODE_OFFLINE)
                                      ? QM_MATCH_MS_SUPPORTED_OFFLINE
                                      : QM_MATCH_MS_SUPPORTED_ONLINE,
                                      NULL);
  if (qm != NULL)
    {
      quvi_media_free((quvi_media_t) qm);
      qm = NULL;
    }
  return (quvi_ok(q));
}

/** @brief Check whether the URL is supported

Check if any of the scripts accepts the URL. Both offline and online
checking is supported.

@note
 - Offline check will fail with most @ref sh_url
 - Online check will resolve @ref sh_url

Type may be a combination.

@code
quvi_supports(q, URL, QUVI_SUPPORTS_OFFLINE,
              QUVI_SUPPORTS_TYPE_PLAYLIST | QUVI_SUPPORTS_TYPE_MEDIA);
@endcode

@ingroup convenience
*/
QuviBoolean quvi_supports(quvi_t handle, const char *url,
                          QuviSupportsMode mode, QuviSupportsType type)
{
  QuviBoolean found;
  _quvi_t q;

  /* If G_DISABLE_CHECKS is defined then the check is not performed. */
  g_return_val_if_fail(handle != NULL, QUVI_FALSE);
  g_return_val_if_fail(url != NULL, QUVI_FALSE);

  q = (_quvi_t) handle;
  q->status.rc = QUVI_OK;
  found = QUVI_FALSE;

  if (type & QUVI_SUPPORTS_TYPE_PLAYLIST)
    found = _supports_playlist(q, url, mode);

  if (q->status.rc == QUVI_OK || q->status.rc == QUVI_ERROR_NO_SUPPORT)
    {
      if (type & QUVI_SUPPORTS_TYPE_MEDIA)
        found = _supports_media(q, url, mode);
    }
  return (found);
}

/* vim: set ts=2 sw=2 tw=72 expandtab: */
