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
  const gchar *url;
  QuviBoolean ok;
  _quvi_net_t n;
  _quvi_t q;
  gint c;

  q = (_quvi_t) l_get_reg_userdata(l, USERDATA_QUVI_T);
  n = NULL;

  if (lua_isstring(l, 1))
    url = lua_tostring(l, 1);
  else
    luaL_error(l, "quvi.fetch: expects an URL argument");
  lua_pop(l, 1);

  n_fetch(q, &n, url);

  ok = quvi_ok(q);
  c = 0; /* No. of quvi.fetch returned values. */

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
