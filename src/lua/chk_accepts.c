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
#include "_quvi_script_s.h"
/* -- */
#include "lua/chk_accepts.h"
#include "lua/getfield.h"

gboolean l_chk_accepts(lua_State *l, _quvi_script_t qs,
                       const gchar *k_accepts, const gchar *k_domains,
                       const gchar *script_func)
{
  gboolean r = FALSE;

  lua_pushstring(l, k_accepts);
  lua_gettable(l, -2);

  if (lua_istable(l, -1))
    {
      const gchar *s = l_getfield_s(l, k_domains,
                                    qs->fpath->str, script_func);

      g_string_assign(qs->domains, s);

      r = l_getfield_b(l, k_accepts, qs->fpath->str, script_func);
    }
  else
    {
      luaL_error(l, "%s: %s: expected to return a table containing table `%s'",
                 qs->fpath->str, script_func, k_accepts);
    }
  lua_pop(l, 1);

  return (r);
}

/* vim: set ts=2 sw=2 tw=72 expandtab: */
