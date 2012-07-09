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
#include "_quvi_scan_s.h"
#include "_quvi_script_s.h"
/* -- */
#include "lua/def.h"
#include "lua/getfield.h"
#include "lua/setfield.h"

static gint _prepend_media_url(gpointer p, const gchar *url)
{
  _quvi_scan_t s = (_quvi_scan_t) p;
  s->url.media = g_slist_prepend(s->url.media, g_strdup(url));
  return (QUVI_OK);
}

static const gchar script_func[] = "parse";

QuviError l_exec_scan_script_parse(gpointer p, gpointer _qss,
                                   const gchar *data)
{
  typedef l_callback_getfield_table_iter_s cb;

  _quvi_script_t qss;
  _quvi_scan_t qs;
  lua_State *l;
  QuviError rc;

  qss = (_quvi_script_t) _qss;
  qs = (_quvi_scan_t) p;

  l = qs->handle.quvi->handle.lua;
  lua_pushnil(l);

  if (luaL_dofile(l, qss->fpath->str))
    luaL_error(l, "%s", lua_tostring(l, -1));

  lua_getglobal(l, script_func);

  if (!lua_isfunction(l, -1))
    {
      luaL_error(l, "%s: `%s' function not found",
                 qss->fpath->str, script_func);
    }

  lua_newtable(l);
  l_set_reg_userdata(l, USERDATA_QUVI_T, (gpointer) qs->handle.quvi);
  l_setfield_b(l, GS_VERBOSE, qs->handle.quvi->opt.scripts.verbose);
  l_setfield_s(l, SS_INPUT_URL, qs->url.input->str);
  l_setfield_s(l, SS_CONTENT, data);

  if (lua_pcall(l, 1, 1, 0))
    {
      g_string_assign(qs->handle.quvi->status.errmsg, lua_tostring(l, -1));
      return (QUVI_ERROR_SCRIPT);
    }

  if (!lua_istable(l, -1))
    {
      luaL_error(l, "%s: expected `%s' function return a table",
                 qss->fpath->str, script_func);
    }

  rc = l_getfield_table_iter_s(l, qs, SS_MEDIA_URL, qss->fpath->str,
                               script_func, (cb) _prepend_media_url);
  if (rc == QUVI_OK)
    qs->url.media = g_slist_reverse(qs->url.media);

  lua_pop(l, 1);

  return (rc);
}

/* vim: set ts=2 sw=2 tw=72 expandtab: */
