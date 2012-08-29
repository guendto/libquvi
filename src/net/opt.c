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

#include <lua.h>
#include <glib.h>

#include "quvi.h"
/* -- */
#include "_quvi_s.h"
#include "_quvi_net_s.h"
#include "_quvi_net_opt_s.h"
/* -- */
#include "net/def.h"
#include "lua/def.h"

gpointer n_opt_new(const QuviFetchOption n, const gchar *vs, const gdouble vn)
{
  _quvi_net_opt_t o = g_new0(struct _quvi_net_opt_s, 1);
  o->value.s = g_string_new(vs);
  o->value.n = vn;
  o->id = n;
  return (o);
}

void n_opt_free(gpointer p, gpointer userdata)
{
  _quvi_net_opt_t o = (_quvi_net_opt_t) p;

  if (p == NULL)
    return;

  g_string_free(o->value.s, TRUE);
  o->value.s = NULL;

  g_free(p);
  p = NULL;
}

void n_chk_callback_opts(_quvi_net_t n, lua_State *l)
{
  _quvi_net_opt_t o;
  gdouble k;

  if (!lua_istable(l, 2))
    return;

  lua_pushnil(l);
  while (lua_next(l, LI_KEY))
    {
      if (lua_isnumber(l, LI_KEY))
        {
          k = lua_tonumber(l, LI_KEY);
          o = NULL;

          switch (lua_type(l, LI_VALUE))
            {
            case LUA_TSTRING:
              o = n_opt_new(k, lua_tostring(l, LI_VALUE), 0);
              break;
            case LUA_TNUMBER:
              o = n_opt_new(k, NULL, lua_tonumber(l, LI_VALUE));
              break;
            default:
              break;
            }

          if (o != NULL)
            n->options = g_slist_prepend(n->options, o);
        }
      lua_pop(l, 1);
    }
  n->options = g_slist_reverse(n->options);
}

/* vim: set ts=2 sw=2 tw=72 expandtab: */
