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
#include "lua/setfield.h"
#include "lua/chk.h"
#include "lua/def.h"
#include "misc/re.h"

/*
 * NOTE: The error messages produced in these functions are intended for
 * developers. They would typically be seen when a new media script is
 * being developed or an old one is being maintained.
 *
 * The messages should be clear, indicating the actual error, minimizing
 * the time spent on locating the actual problem in the script.
 */

static const gchar script_func[] = "parse";

static void _foreach_video_property(lua_State *l, _quvi_media_t qm,
                                    _quvi_media_stream_t qms)
{
  lua_pushnil(l);
  while (lua_next(l, LI_KEY))
    {
      l_chk_assign_n(l, MSS_VIDEO_BITRATE_KBIT_S, &qms->video.bitrate_kbit_s);
      l_chk_assign_s(l, MSS_VIDEO_ENCODING, qms->video.encoding);
      l_chk_assign_n(l, MSS_VIDEO_HEIGHT, &qms->video.height);
      l_chk_assign_n(l, MSS_VIDEO_WIDTH, &qms->video.width);
      lua_pop(l, 1);
    }
}

static void _foreach_audio_property(lua_State *l, _quvi_media_t qm,
                                    _quvi_media_stream_t qms)
{
  lua_pushnil(l);
  while (lua_next(l, LI_KEY))
    {
      l_chk_assign_n(l, MSS_AUDIO_BITRATE_KBIT_S, &qms->audio.bitrate_kbit_s);
      l_chk_assign_s(l, MSS_AUDIO_ENCODING, qms->audio.encoding);
      lua_pop(l, 1);
    }
}

static void _foreach_flag_property(lua_State *l, _quvi_media_t qm,
                                   _quvi_media_stream_t qms)
{
  lua_pushnil(l);
  while (lua_next(l, LI_KEY))
    {
      l_chk_assign_b(l, MSS_FLAGS_BEST, &qms->flags.best);
      lua_pop(l, 1);
    }
}

typedef void (*foreach_cb)(lua_State*, _quvi_media_t, _quvi_media_stream_t);

static void _chk_stream_sublevel(const gchar *level, lua_State *l,
                                 _quvi_media_t qm, _quvi_media_stream_t qms,
                                 foreach_cb cb)
{
  if (lua_isstring(l, LI_KEY) && lua_istable(l, LI_VALUE))
    {
      if (g_strcmp0(lua_tostring(l, LI_KEY), level) == 0)
        cb(l, qm, qms);
    }
}

static gpointer _media_stream_new()
{
  _quvi_media_stream_t qms = g_new0(struct _quvi_media_stream_s, 1);
  qms->video.encoding = g_string_new(NULL);
  qms->audio.encoding = g_string_new(NULL);
  qms->container = g_string_new(NULL);
  qms->fmt_id = g_string_new(NULL);
  qms->url = g_string_new(NULL);
  return (qms);
}

static void _has_stream_url(lua_State *l, _quvi_media_stream_t qms,
                            const gchar *script_path, const gint i)
{
  if (qms->url->len ==0)
    {
      luaL_error(l, "%s: %s: must return a media stream URL in "
                 "`qargs.%s[%d].%s'", script_path, script_func,
                 MS_STREAMS, i, MSS_URL);
    }
}

static _quvi_media_stream_t _new_stream(lua_State *l, _quvi_media_t qm,
                                        const gchar *script_path,
                                        const gint i)
{
  _quvi_media_stream_t qms = _media_stream_new();

  lua_pushnil(l);
  while (lua_next(l, LI_KEY)) /* For each qargs.stream property */
    {
      _chk_stream_sublevel(MSS_VIDEO, l, qm, qms, _foreach_video_property);
      _chk_stream_sublevel(MSS_AUDIO, l, qm, qms, _foreach_audio_property);
      _chk_stream_sublevel(MSS_FLAGS, l, qm, qms, _foreach_flag_property);
      l_chk_assign_s(l, MSS_CONTAINER, qms->container);
      l_chk_assign_s(l, MSS_FORMAT_ID, qms->fmt_id);
      l_chk_assign_s(l, MSS_URL, qms->url);
      lua_pop(l, 1);
    }
  _has_stream_url(l, qms, script_path, i);
  return (qms);
}

static void _chk_stream_fmt_ids(lua_State *l, _quvi_media_t qm,
                                 const gchar *script_path)
{
  _quvi_media_stream_t qms;
  GSList *curr;
  gint i;

  if (g_slist_length(qm->streams) < 2)
    return;

  curr = qm->streams;
  i = 1;

  while (curr != NULL)
    {
      qms = (_quvi_media_stream_t) curr->data;
      if (qms->fmt_id->len ==0)
        {
          g_warning("%s: %s: `qargs.%s[%d].%s' should not be empty, "
                    "when there are >1 streams the scripts are "
                    "expected to set a format ID for each stream",
                    script_path, script_func, MS_STREAMS, i, MSS_FORMAT_ID);
        }
      curr = g_slist_next(curr);
      ++i;
    }
}

static void _foreach_stream(lua_State *l, _quvi_media_t qm,
                            const gchar *script_path)
{
  gint i = 0;

  lua_pushnil(l);
  while (lua_next(l, LI_KEY))
    {
      if (lua_istable(l, LI_VALUE))
        {
          _quvi_media_stream_t qms = _new_stream(l, qm, script_path, ++i);
          qm->streams = g_slist_prepend(qm->streams, qms);
        }
      lua_pop(l, 1);
    }
  qm->streams = g_slist_reverse(qm->streams);
  _chk_stream_fmt_ids(l, qm, script_path);
}

/* Check for 'qargs.streams'. This is the only mandatory data. */
static void _chk_streams(lua_State *l, _quvi_media_t qm,
                         const gchar *script_path)
{
  lua_pushstring(l, MS_STREAMS);
  lua_gettable(l, LI_KEY);

  if (lua_istable(l, LI_VALUE))
    _foreach_stream(l, qm, script_path);
  else
    {
      luaL_error(l, "%s: %s: must return a dictionary containing "
                 "the `qargs.%s'", script_path, script_func, MS_STREAMS);
    }
  lua_pop(l, 1);

  if (g_slist_length(qm->streams) ==0)
    {
      luaL_error(l, "%s: %s: must return at least one media stream",
                 script_path, script_func);
    }
}

/* Check for optional media properties, e.g. title. */
static void _chk_optional(lua_State *l, _quvi_media_t qm)
{
  lua_pushnil(l);
  while (lua_next(l, LI_KEY))
    {
      l_chk_assign_n(l, MS_START_TIME_MS, &qm->start_time_ms);
      l_chk_assign_n(l, MS_DURATION_MS, &qm->duration_ms);
      l_chk_assign_s(l, MS_THUMB_URL, qm->url.thumbnail);
      l_chk_assign_s(l, MS_TITLE, qm->title);
      l_chk_assign_s(l, MS_ID, qm->id);
      lua_pop(l, 1);
    }
}

/* Check for the goto URL instruction. */
static gboolean _chk_goto_instr(lua_State *l, _quvi_media_t qm)
{
  lua_pushnil(l);
  while (lua_next(l, LI_KEY))
    {
      l_chk_assign_s(l, MS_GOTO_URL, qm->url.redirect_to);
      lua_pop(l, 1);
    }
  return ((qm->url.redirect_to->len >0) ? TRUE:FALSE);
}

extern QuviError l_exec_util_convert_entities(_quvi_media_t qm);

QuviError l_exec_media_script_parse(gpointer p, GSList *sl)
{
  _quvi_script_t qs;
  _quvi_media_t qm;
  lua_State *l;
  QuviError rc;

  qm = (_quvi_media_t) p;
  l = qm->handle.quvi->handle.lua;
  rc = QUVI_OK;

  qs = (_quvi_script_t) sl->data;
  lua_getglobal(l, script_func);

  if (!lua_isfunction(l, -1))
    luaL_error(l, "%s: function `%s' not found", qs->fpath->str, script_func);

  lua_newtable(l);
  l_set_reg_userdata(l, USERDATA_QUVI_T, (gpointer) qm->handle.quvi);
  l_setfield_b(l, GS_VERBOSE, qm->handle.quvi->opt.scripts.verbose);
  l_setfield_s(l, MS_INPUT_URL, qm->url.input->str);

  if (lua_pcall(l, 1, 1, 0))
    {
      g_string_assign(qm->handle.quvi->status.errmsg, lua_tostring(l, -1));
      return (QUVI_ERROR_SCRIPT);
    }

  if (!lua_istable(l, -1))
    {
      luaL_error(l, "%s: %s: must return a dictionary, typically `qargs'",
                 qs->fpath->str, script_func);
    }

  if (_chk_goto_instr(l, qm) == FALSE)
    {
      _chk_streams(l, qm, qs->fpath->str);
      _chk_optional(l, qm);
      rc = l_exec_util_convert_entities(qm);
    }
  lua_pop(l, 1);

  return (rc);
}

/* vim: set ts=2 sw=2 tw=72 expandtab: */
