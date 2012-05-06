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

#include <lauxlib.h>
#include <glib.h>

#include "quvi.h"
/* -- */
#include "_quvi_s.h"
#include "_quvi_playlist_s.h"
#include "_quvi_script_s.h"
/* -- */
#include "lua/def.h"
#include "lua/getfield.h"
#include "lua/setfield.h"
#include "misc/re.h"

static const gchar script_func[] = "parse";

static void _get(lua_State *l, const gchar *k,
                 gpointer dst, const gchar *script_path)
{
  const gchar *s = l_getfield_s(l, k, script_path, script_func);
  if (s != NULL)
    {
      gchar *u = m_trim_ws(s);
      if (u != NULL)
        {
          g_string_assign((GString*) dst, u);
          g_free(u);
          u = NULL;
        }
    }
}

static gint _prepend_media_url(gpointer p, const gchar *url)
{
  _quvi_playlist_t pl = (_quvi_playlist_t) p;
  pl->url.media = g_slist_prepend(pl->url.media, g_strdup(url));
  return (QUVI_OK);
}

QuviError l_exec_playlist_script_parse(gpointer p, GSList *sl)
{
  const _quvi_script_t qs = (_quvi_script_t) sl->data;
  _quvi_playlist_t pl = (_quvi_playlist_t) p;
  lua_State *l = pl->handle.quvi->handle.lua;
  QuviError rc = QUVI_OK;

  lua_getglobal(l, script_func);

  if (!lua_isfunction(l, -1))
    luaL_error(l, "%s: `%s' function not found", qs->fpath->str, script_func);

  lua_newtable(l);
  l_set_reg_userdata(l, USERDATA_QUVI_T, (gpointer) pl->handle.quvi);
  l_setfield_b(l, GS_VERBOSE, pl->handle.quvi->opt.scripts.verbose);
  l_setfield_s(l, PS_INPUT_URL, pl->url.input->str);

  if (lua_pcall(l, 1, 1, 0))
    {
      g_string_assign(pl->handle.quvi->status.errmsg, lua_tostring(l, -1));
      return (QUVI_ERROR_SCRIPT);
    }

  if (!lua_istable(l, -1))
    {
      luaL_error(l, "%s: expected `%s' function return a table",
                 qs->fpath->str, script_func);
    }

  {
    typedef l_callback_getfield_table_iter_s cb;
    const gchar *s = qs->fpath->str;

    _get(l, PS_ID, (gpointer) pl->id.playlist, s);

    rc = l_getfield_table_iter_s(l, pl, PS_MEDIA_URL, s,
                                 script_func, (cb) _prepend_media_url);
    if (rc == QUVI_OK)
      pl->url.media = g_slist_reverse(pl->url.media);
  }

  lua_pop(l, 1);

  return (rc);
}

/* vim: set ts=2 sw=2 tw=72 expandtab: */
