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
#include <lualib.h>
#include <glib.h>

#include "quvi.h"
/* -- */
#include "_quvi_s.h"
#include "_quvi_media_s.h"
#include "_quvi_net_s.h"
/* -- */
#include "lua/load_util_script.h"

static const gchar script_fname[]= "to_file_ext.lua";
static const gchar script_func[] = "to_file_ext";

QuviError l_exec_util_to_file_ext(_quvi_media_t m, _quvi_net_t n)
{
  _quvi_t q = m->handle.quvi;
  lua_State *l = q->handle.lua;
  QuviError rc = l_load_util_script(m, script_fname, script_func);

  if (rc != QUVI_OK)
    return (rc);

  lua_pushstring(l, n->verify.content_type->str);

  /* 2=qargs,title [qargs: set in l_load_util_script]
   * 1=returns a string */
  if (lua_pcall(l, 2, 1, 0))
    {
      g_string_assign(q->status.errmsg, lua_tostring(l, -1));
      return (QUVI_ERROR_SCRIPT);
    }

  if (lua_isstring(l, -1))
    g_string_assign(m->file_ext, lua_tostring(l, -1));
  else
    luaL_error(l, "%s: did not return a string", script_func);

  lua_pop(l, 1);

  return (rc);
}

/* vim: set ts=2 sw=2 tw=72 expandtab: */
