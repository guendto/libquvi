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
#include "lua/getfield.h"
#include "lua/chk.h"
#include "lua/def.h"
#include "misc/re.h"

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

/*
 * Return the value of the named (`w') string. The value is trimmed
 * of any extra whitespace (e.g. leading, trailing).
 *
 * NOTE: g_free the returned value when done using it.
 */
gboolean l_chk_s(lua_State *l, const gchar *w, gchar **v)
{
  if (lua_isstring(l, LI_KEY) && lua_isstring(l, LI_VALUE))
    {
      if (g_strcmp0(lua_tostring(l, LI_KEY), w) == 0)
        {
          *v = m_trim_ws(lua_tostring(l, LI_VALUE));
          return (TRUE);
        }
    }
  return (FALSE);
}

gboolean l_chk_assign_s(lua_State *l, const gchar *k, GString *v)
{
  gchar *s = NULL;
  if (l_chk_s(l, k, &s) == TRUE)
    {
      g_string_assign(v, s);
      g_free(s);
      s = NULL;
      return (TRUE);
    }
  return (FALSE);
}

gboolean l_chk_n(lua_State *l, const gchar *w, gdouble *v)
{
  if (lua_isstring(l, LI_KEY) && lua_isnumber(l, LI_VALUE))
    {
      if (g_strcmp0(lua_tostring(l, LI_KEY), w) == 0)
        {
          *v = lua_tonumber(l, LI_VALUE);
          return (TRUE);
        }
    }
  return (FALSE);
}

gboolean l_chk_assign_n(lua_State *l, const gchar *k, gdouble *v)
{
  gdouble n = 0;
  if (l_chk_n(l, k, &n) == TRUE)
    {
      *v = n;
      return (TRUE);
    }
  return (FALSE);
}

gboolean l_chk_b(lua_State *l, const gchar *w, gboolean *v)
{
  if (lua_isstring(l, LI_KEY) && lua_isboolean(l, LI_VALUE))
    {
      if (g_strcmp0(lua_tostring(l, LI_KEY), w) == 0)
        {
          *v = lua_toboolean(l, LI_VALUE);
          return (TRUE);
        }
    }
  return (FALSE);
}

gboolean l_chk_assign_b(lua_State *l, const gchar *k, gboolean *v)
{
  gboolean b = 0;
  if (l_chk_b(l, k, &b) == TRUE)
    {
      *v = b;
      return (TRUE);
    }
  return (FALSE);
}

/* vim: set ts=2 sw=2 tw=72 expandtab: */
