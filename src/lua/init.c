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

/* 'quvi' object functions for media scripts, e.g. 'quvi.fetch' */

extern gint l_quvi_resolve(lua_State*);
extern gint l_quvi_fetch(lua_State*);

static const luaL_Reg reg_meth[] =
{
  {"resolve", l_quvi_resolve},
  {"fetch", l_quvi_fetch},
  {NULL, NULL}
};

QuviError l_init(_quvi_t q)
{
  q->handle.lua = (lua_State*)luaL_newstate();
  if (q->handle.lua == NULL)
    return (QUVI_ERROR_LUA_INIT);

  luaL_openlibs(q->handle.lua);
  luaL_openlib(q->handle.lua, "quvi", reg_meth, 1);

  return (QUVI_OK);
}

/* vim: set ts=2 sw=2 tw=72 expandtab: */
