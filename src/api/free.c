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

/** @file free.c */

#include "config.h"

#include <lualib.h>
#include <proxy.h>
#include <glib.h>

#include "quvi.h"
/* -- */
#include "_quvi_s.h"
#include "_quvi_script_s.h"
/* -- */
#include "misc/script_free.h"

/** @cond NODOC */
extern void c_close(_quvi_t);
/** @endcond */

/** @brief Free all of memory used by a library handle
@note If handle is NULL the function simply returns
@sa @ref getting_started
@ingroup lib
*/
void quvi_free(quvi_t handle)
{
  _quvi_t q = (_quvi_t) handle;

  if (handle == NULL)
    return;

  c_close(q);

  /* Strings. */

  g_string_free(q->status.errmsg, TRUE);
  q->status.errmsg = NULL;

  /* Scripts. */

#ifdef HAVE_GLIB_2_28
  g_slist_free_full(q->scripts.playlist, m_script_free);
#else
  g_slist_foreach(q->scripts.playlist, m_script_free, NULL);
  g_slist_free(q->scripts.playlist);
#endif
  q->scripts.playlist = NULL;

#ifdef HAVE_GLIB_2_28
  g_slist_free_full(q->scripts.media, m_script_free);
#else
  g_slist_foreach(q->scripts.media, m_script_free, NULL);
  g_slist_free(q->scripts.media);
#endif
  q->scripts.media = NULL;

#ifdef HAVE_GLIB_2_28
  g_slist_free_full(q->scripts.scan, m_script_free);
#else
  g_slist_foreach(q->scripts.scan, m_script_free, NULL);
  g_slist_free(q->scripts.scan);
#endif
  q->scripts.scan = NULL;

#ifdef HAVE_GLIB_2_28
  g_slist_free_full(q->scripts.util, m_script_free);
#else
  g_slist_foreach(q->scripts.util, m_script_free, NULL);
  g_slist_free(q->scripts.util);
#endif
  q->scripts.util = NULL;

  /* Handles. */

  if (q->handle.lua != NULL)
    {
      lua_close(q->handle.lua);
      q->handle.lua = NULL;
    }

  if (q->handle.proxy != NULL)
    {
      px_proxy_factory_free(q->handle.proxy);
      q->handle.proxy = NULL;
    }

  g_free(q);
  q = NULL;
}

/* vim: set ts=2 sw=2 tw=72 expandtab: */
