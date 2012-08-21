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

#include <string.h>
#include <glib.h>

#include "quvi.h"
/* -- */
#include "_quvi_s.h"
#include "_quvi_playlist_s.h"
#include "_quvi_net_s.h"
#include "_quvi_script_s.h"
/* -- */
#include "misc/match_playlist_script.h"
#include "misc/playlist.h"
#include "misc/resolve.h"
#include "net/handle.h"
#include "lua/exec.h"

extern QuviError l_match_url_to_playlist_script(_quvi_playlist_t, GSList**);
extern const gchar *show_script; /* m_scan_scripts */

typedef QuviMatchPlaylistScriptMode _qm_mode;

QuviError m_match_playlist_script(_quvi_t q, _quvi_playlist_t *p,
                                  const gchar *url, const _qm_mode mode,
                                  gchar **result)
{
  gboolean resolve_flag;
  QuviError rc;
  GSList *s;

  resolve_flag = (mode != QM_MATCH_PS_SUPPORTED_OFFLINE)
                 ? TRUE
                 : FALSE;

  *p = m_playlist_new(q, url);

  if (resolve_flag == TRUE) /* Resolve URL redirection. */
    {
      m_resolve(q, url, (*p)->url.input);
      if (quvi_ok(q) == QUVI_FALSE)
        return (q->status.rc);
    }

  rc = l_match_url_to_playlist_script(*p, &s);
  if (rc == QUVI_ERROR_NO_SUPPORT)
    {
      g_string_printf((*p)->handle.quvi->status.errmsg,
                      "no support: %s", url);
      return (rc);
    }
  else if (rc != QUVI_OK)
    return (rc);

  if (show_script != NULL && strlen(show_script) >0)
    {
      const _quvi_script_t qs = (const _quvi_script_t) s->data;

      g_message("libquvi: %s: %s: input URL accepted",
                __func__, qs->fpath->str);
    }

  switch (mode)
    {
    case QM_MATCH_PS_PARSE:
      rc = l_exec_playlist_script_parse(*p, s);
      break;
    case QM_MATCH_PS_SUPPORTED_OFFLINE:
    case QM_MATCH_PS_SUPPORTED_ONLINE:
      break;
    }
  return (rc);
}

/* vim: set ts=2 sw=2 tw=72 expandtab: */
