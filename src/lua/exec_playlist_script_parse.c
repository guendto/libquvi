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
#include "lua/setfield.h"
#include "lua/chk.h"
#include "lua/def.h"

/*
 * NOTE: The error messages produced in these functions are intended for
 * developers. They would typically be seen when a new media script is
 * being developed or an old one is being maintained.
 *
 * The messages should be clear, indicating the actual error, minimizing
 * the time spent on locating the actual problem in the script.
 */

static const gchar script_func[] = "parse";

static void _chk_optional(lua_State *l, _quvi_playlist_t qp)
{
  lua_pushnil(l);
  while (lua_next(l, LI_KEY))
    {
      l_chk_assign_s(l, PS_ID, qp->id.playlist);
      lua_pop(l, 1);
    }
}

static void _foreach_media_url(lua_State *l, _quvi_playlist_t qp,
                               const gchar *script_path)
{
  lua_pushnil(l);
  while (lua_next(l, LI_KEY))
    {
      if (lua_isstring(l, LI_KEY) && lua_isstring(l, LI_VALUE))
        {
          const gchar *url = lua_tostring(l, LI_VALUE);
          qp->url.media = g_slist_prepend(qp->url.media, g_strdup(url));
        }
      lua_pop(l, 1);
    }
  qp->url.media = g_slist_reverse(qp->url.media);
}

/* Check for 'qargs.media_url'. */
static void _chk_media_url(lua_State *l, _quvi_playlist_t qp,
                           const gchar *script_path)
{
  lua_pushstring(l, PS_MEDIA_URL);
  lua_gettable(l, LI_KEY);

  if (lua_istable(l, LI_VALUE))
    _foreach_media_url(l, qp, script_path);
  else
    {
      g_warning("%s: %s: should return a dictionary containing "
                "the `qargs.%s'", script_path, script_func,
                PS_MEDIA_URL);
    }
  lua_pop(l, 1);
}

QuviError l_exec_playlist_script_parse(gpointer p, GSList *sl)
{
  _quvi_playlist_t qp;
  _quvi_script_t qs;
  lua_State *l;

  qp = (_quvi_playlist_t) p;
  l = qp->handle.quvi->handle.lua;

  qs = (_quvi_script_t) sl->data;
  lua_getglobal(l, script_func);

  if (!lua_isfunction(l, -1))
    luaL_error(l, "%s: function `%s' not found", qs->fpath->str, script_func);

  lua_newtable(l);
  l_set_reg_userdata(l, USERDATA_QUVI_T, (gpointer) qp->handle.quvi);
  l_setfield_b(l, GS_VERBOSE, qp->handle.quvi->opt.scripts.verbose);
  l_setfield_s(l, PS_INPUT_URL, qp->url.input->str);

  if (lua_pcall(l, 1, 1, 0))
    {
      g_string_assign(qp->handle.quvi->status.errmsg, lua_tostring(l, -1));
      return (QUVI_ERROR_SCRIPT);
    }

  if (!lua_istable(l, -1))
    {
      luaL_error(l, "%s: %s: must return a dictionary, typically `qargs'",
                 qs->fpath->str, script_func);
    }

  _chk_optional(l, qp);
  _chk_media_url(l, qp, qs->fpath->str);
  lua_pop(l, 1);

  return (QUVI_OK);
}

/* vim: set ts=2 sw=2 tw=72 expandtab: */
