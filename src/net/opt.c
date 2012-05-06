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

#include <lua.h>
#include <glib.h>

#include "quvi.h"
/* -- */
#include "_quvi_s.h"
#include "_quvi_net_s.h"
#include "_quvi_net_opt_s.h"
/* -- */
#include "net/def.h"

gpointer n_opt_new(const gchar *o, const gchar *v)
{
  _quvi_net_opt_t p = g_new0(struct _quvi_net_opt_s, 1);
  p->name = g_string_new(o);
  p->val  = g_string_new(v);
  return (p);
}

void n_opt_free(gpointer p, gpointer userdata)
{
  _quvi_net_opt_t o = (_quvi_net_opt_t) p;

  if (p == NULL)
    return;

  g_string_free(o->name, TRUE);
  o->name = NULL;

  g_string_free(o->val, TRUE);
  o->val = NULL;

  g_free(p);
  p = NULL;
}

const gchar *n_opt_name[] =
{
  MSO_ARBITRARY_COOKIE,
  MSO_FROM_CHARSET,
  MSO_USER_AGENT,
  NULL
};

void n_chk_callback_opts(_quvi_net_t n, lua_State *l)
{
  gint i = -1;
  while (n_opt_name[++i] != NULL)
    {
      lua_pushstring(l, n_opt_name[i]);
      lua_gettable(l, 2);
      if (lua_isstring(l, -1))
        {
          const gchar *v = lua_tostring(l, -1);
          const _quvi_net_opt_t o = n_opt_new(n_opt_name[i], v);
          n->options = g_slist_append(n->options, o);
        }
    }
}

/* vim: set ts=2 sw=2 tw=72 expandtab: */
