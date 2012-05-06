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
#include "_quvi_net_s.h"
#include "_quvi_net_resolve_s.h"
/* -- */
#include "lua/def.h"
#include "lua/getfield.h"
#include "net/handle.h"
#include "net/fetch.h"

gint l_quvi_fetch(lua_State *l)
{
  _quvi_t q = (_quvi_t) l_get_reg_userdata(l, USERDATA_QUVI_T);
  gint c = 0; /* Count of returned (pushed) values. */
  const gchar *url = luaL_checkstring(l, 1);
  QuviBoolean ok = QUVI_FALSE;
  _quvi_net_t n = NULL;

  n_fetch(q, &n, url);
  ok = quvi_ok(q);

  if (ok == QUVI_TRUE)
    {
      lua_pushnil(l);
      /* The string cannot contain embedded zeros; it is assumed to end
       * at the first zero. <http://pgl.yoyo.org/luai/i/lua_pushstring> */
      lua_pushstring(l, n->fetch.content->str);
      ++c;
    }

  n_free(n);
  n = NULL;

  return ((ok == QUVI_FALSE)
          ? luaL_error(l, "%s", q->status.errmsg->str)
          : c);
}

/* vim: set ts=2 sw=2 tw=72 expandtab: */
