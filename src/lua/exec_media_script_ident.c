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
#include "_quvi_media_s.h"
#include "_quvi_script_s.h"
/* -- */
#include "lua/def.h"
#include "lua/getfield.h"
#include "lua/setfield.h"

static const gchar script_func[] = "ident";

QuviError l_exec_media_script_ident(gpointer p, GSList *sl)
{
  const _quvi_script_t qs = (_quvi_script_t) sl->data;
  _quvi_media_t m = (_quvi_media_t) p;
  lua_State *l = m->handle.quvi->handle.lua;
  QuviError rc = QUVI_ERROR_NO_SUPPORT;

  lua_pushnil(l);
  lua_pushnil(l);
  lua_setglobal(l, script_func);

  if (luaL_dofile(l, qs->fpath->str))
    luaL_error(l, "%s", lua_tostring(l, -1));

  lua_getglobal(l, script_func);

  if (!lua_isfunction(l, -1))
    {
      luaL_error(l, "%s: `%s' function not found",
                 qs->fpath->str, script_func);
    }

  lua_newtable(l);
  l_setfield_b(l, GS_VERBOSE, m->handle.quvi->opt.scripts.verbose);
  l_setfield_s(l, MS_INPUT_URL, m->url.input->str);

  if (lua_pcall(l, 1, 1, 0))
    {
      g_string_assign(m->handle.quvi->status.errmsg, lua_tostring(l, -1));
      return (QUVI_ERROR_SCRIPT);
    }

  if (lua_istable(l, -1))
    {
      const glong c = (glong) l_getfield_n(l, MS_CATEGORIES,
                                           qs->fpath->str, script_func);
      const gboolean r =
        l_getfield_b(l, MS_ACCEPTS, qs->fpath->str, script_func);

      if (r == TRUE)
        {
          rc = (c & m->handle.quvi->opt.scripts.category)
               ? QUVI_OK
               : QUVI_ERROR_NO_SUPPORT;
        }
    }
  else
    {
      luaL_error(l, "%s: expected `%s' to return a table",
                 qs->fpath->str, script_func);
    }

  lua_pop(l, 1);

  return (rc);
}

/* vim: set ts=2 sw=2 tw=72 expandtab: */
