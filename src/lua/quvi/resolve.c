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
/* -- */
#include "lua/def.h"
#include "lua/getfield.h"
#include "net/handle.h"
#include "misc/resolve.h"

/* quvi.resolve is callable from the Lua scripts.
 * Ignores the QUVI_OPTION_RESOLVE_URL_REDIRECTIONS value. */
gint l_quvi_resolve(lua_State *l)
{
  _quvi_t q = (_quvi_t) l_get_reg_userdata(l, USERDATA_QUVI_T);
  const gchar *url = luaL_checkstring(l, 1);
  gchar *r_url = m_resolve(q, url, TRUE /* See comment above. */);
  gint c = 0; /* Count of returned (pushed) values. */
  const QuviBoolean ok = quvi_ok(q);

  if (ok == QUVI_TRUE)
    {
      lua_pushnil(l);
      if (r_url != NULL)  /* New location. */
        {
          lua_pushboolean(l, 1);
          ++c;
          lua_pushstring(l, r_url);
          g_free(r_url);
          r_url = NULL;
        }
      else
        lua_pushboolean(l, 0); /* No redirection. */
      ++c;
    }
  else
    luaL_error(l, "%s", q->status.errmsg->str);

  return (c);
}

/* vim: set ts=2 sw=2 tw=72 expandtab: */
