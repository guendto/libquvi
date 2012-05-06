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
#include "_quvi_media_s.h"
#include "_quvi_script_s.h"
/* -- */
#include "lua/def.h"
#include "lua/getfield.h"
#include "lua/setfield.h"
#include "misc/re.h"

static const gchar script_func[] = "parse";

typedef enum { String, Number } Type;

static gdouble _get(lua_State *l, const gchar *k,
                    gpointer dst, Type t,
                    const gchar *script_path)
{
  if (t == String)
    {
      const gchar *s = l_getfield_s(l, k, script_path, script_func);
      if (s != NULL)
        {
          gchar *u = m_trim_ws(s);
          if (u != NULL)
            {
              g_string_assign((GString*) dst, u);
              g_free(u);
              u = NULL;
              return ((((GString*) dst))->len);
            }
        }
    }
  else if (t == Number)
    return (l_getfield_n(l, k, script_path, script_func));

  return (0);
}

extern QuviError l_exec_util_convert_entities(_quvi_media_t m);

QuviError l_exec_media_script_parse(gpointer p, GSList *sl)
{
  const _quvi_script_t qs = (_quvi_script_t) sl->data;
  _quvi_media_t m = (_quvi_media_t) p;
  lua_State *l = m->handle.quvi->handle.lua;
  QuviError rc = QUVI_OK;

  lua_getglobal(l, script_func);

  if (!lua_isfunction(l, -1))
    luaL_error(l, "%s: `%s' function not found", qs->fpath->str, script_func);

  lua_newtable(l);
  l_set_reg_userdata(l, USERDATA_QUVI_T, (gpointer) m->handle.quvi);
  l_setfield_b(l, GS_VERBOSE, m->handle.quvi->opt.scripts.verbose);
  l_setfield_s(l, MS_REQ_FORMAT,  m->handle.quvi->opt.format->str);
  l_setfield_s(l, MS_INPUT_URL,   m->url.input->str);
  l_setfield_s(l, MS_GOTO_URL,    MS_EMPTY);
  l_setfield_s(l, MS_START_TIME,  MS_EMPTY);
  l_setfield_s(l, MS_THUMB_URL,   MS_EMPTY);
  l_setfield_n(l, MS_DURATION_MS, 0);

  if (lua_pcall(l, 1, 1, 0))
    {
      g_string_assign(m->handle.quvi->status.errmsg, lua_tostring(l, -1));
      return (QUVI_ERROR_SCRIPT);
    }

  if (!lua_istable(l, -1))
    {
      luaL_error(l, "%s: expected `%s' function return a table",
                 qs->fpath->str, script_func);
    }

  {
    /* Check if media script set a redirection. */

    g_string_assign(m->url.redirect_to,
                    l_getfield_s(l, MS_GOTO_URL,
                                 qs->fpath->str, script_func));

    if (m->url.redirect_to->len ==0) /* No. */
      {
        const gchar *p = qs->fpath->str;

        _get(l, MS_STREAM_URL, (gpointer) m->url.stream,    String, p);
        _get(l, MS_START_TIME, (gpointer) m->start_time,    String, p);
        _get(l, MS_THUMB_URL,  (gpointer) m->url.thumbnail, String, p);
        _get(l, MS_TITLE,      (gpointer) m->title,         String, p);
        _get(l, MS_SITE,       (gpointer) m->id.site,       String, p);
        _get(l, MS_ID,         (gpointer) m->id.media,      String, p);

        m->duration_ms = _get(l, MS_DURATION_MS, NULL, Number, p);

        if (rc == QUVI_OK)
          rc = l_exec_util_convert_entities(m);
      }
  }

  lua_pop(l, 1);

  return (rc);
}

/* vim: set ts=2 sw=2 tw=72 expandtab: */
