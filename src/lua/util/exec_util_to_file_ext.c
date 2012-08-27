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

#include "config.h"

#include <lauxlib.h>
#include <lualib.h>
#include <glib.h>

#include "quvi.h"
/* -- */
#include "_quvi_s.h"
#include "_quvi_verify_s.h"
#include "_quvi_net_s.h"
/* -- */
#include "lua/load_util_script.h"

static const gchar script_fname[]= "to_file_ext.lua";
static const gchar script_func[] = "to_file_ext";

QuviError l_exec_util_to_file_ext(_quvi_verify_t v, _quvi_net_t n)
{
  lua_State *l;
  QuviError rc;
  _quvi_t q;

  q = v->handle.quvi;
  rc = l_load_util_script(q, script_fname, script_func);

  if (rc != QUVI_OK)
    return (rc);

  l = q->handle.lua;
  lua_pushstring(l, n->verify.content_type->str);

  /* 2=qargs,title [qargs: set in l_load_util_script]
   * 1=returns a string */
  if (lua_pcall(l, 2, 1, 0))
    {
      g_string_assign(q->status.errmsg, lua_tostring(l, -1));
      return (QUVI_ERROR_SCRIPT);
    }

  if (!lua_isstring(l, -1))
    luaL_error(l, "%s: did not return a string", script_func);

  g_string_assign(v->file_ext, lua_tostring(l,-1));
  lua_pop(l, 1);

  return (QUVI_OK);
}

/* vim: set ts=2 sw=2 tw=72 expandtab: */
