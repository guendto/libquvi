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
 * developers. They would typically be seen when a new script is being
 * developed.
 *
 * The messages should be clear, indicating the actual error, minimizing
 * the time spent on locating the actual problem in the script.
 */

static const gchar script_func[] = "ident";

static QuviError _chk_results(lua_State *l, _quvi_script_t qs)
{
  const QuviError rc = (l_chk_accepts(l, qs, PS_ACCEPTS,
                                      PS_DOMAINS, script_func) == TRUE)
                       ? QUVI_OK
                       : QUVI_ERROR_NO_SUPPORT;
  lua_pop(l, 1);
  return (rc);
}

QuviError l_exec_playlist_script_ident(gpointer p, GSList *sl)
{
  _quvi_playlist_t qp;
  _quvi_script_t qs;
  lua_State *l;

  qp = (_quvi_playlist_t) p;
  l = qp->handle.quvi->handle.lua;

  qs = (_quvi_script_t) sl->data;
  lua_pushnil(l);

  if (luaL_dofile(l, qs->fpath->str))
    luaL_error(l, "%s", lua_tostring(l, -1));

  lua_getglobal(l, script_func);

  if (!lua_isfunction(l, -1))
    luaL_error(l, "%s: function `%s' not found", qs->fpath->str, script_func);

  lua_newtable(l);
  l_setfield_b(l, GS_VERBOSE, qp->handle.quvi->opt.scripts.verbose);
  l_setfield_s(l, PS_INPUT_URL, qp->url.input->str);

  if (lua_pcall(l, 1, 1, 0))
    {
      g_string_assign(qp->handle.quvi->status.errmsg, lua_tostring(l, -1));
      return (QUVI_ERROR_SCRIPT);
    }

  if (!lua_istable(l, -1))
    {
      luaL_error(l, "%s: %s: must return a dictionary",
                 qs->fpath->str, script_func);
    }
  return (_chk_results(l, qs));
}

/* vim: set ts=2 sw=2 tw=72 expandtab: */
