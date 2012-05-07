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

/** @file script_next.c */

#include "config.h"

#include <glib.h>

#include "quvi.h"
/* -- */
#include "_quvi_s.h"
/* -- */
#include "misc/sort.h"

/** @cond NODOC */
#define _W "libquvi: %s: %d"
/** @endcond */

/** @brief Traverse to next media script
@return QUVI_TRUE if succeeded, otherwise QUVI_FALSE
@ingroup script
*/
QuviBoolean quvi_script_next(quvi_t handle, QuviScriptType type)
{
  _quvi_t q = (_quvi_t) handle;
  QuviBoolean r = QUVI_FALSE;
  GSList *l = NULL;

  /* If G_DISABLE_CHECKS is defined then the check is not performed. */
  g_return_val_if_fail(handle != NULL, QUVI_FALSE);

  switch (type)
    {
    case QUVI_SCRIPT_TYPE_PLAYLIST:
      l = q->scripts.playlist;
      break;

    default:
      g_warning(_W, __func__, (gint) type);
    case QUVI_SCRIPT_TYPE_MEDIA:
      l = q->scripts.media;
      break;

    case QUVI_SCRIPT_TYPE_SCAN:
      l = q->scripts.scan;
      break;
    }

  if (q->opt.scripts.update_order == TRUE)
    {
      l = g_slist_sort_with_data(l, m_sort_scripts, q);
      q->opt.scripts.update_order = FALSE;
      switch (type) /* Reset */
        {
        case QUVI_SCRIPT_TYPE_PLAYLIST:
          q->scripts.curr.playlist = NULL;
          break;

        case QUVI_SCRIPT_TYPE_MEDIA:
        default:
          q->scripts.curr.media = NULL;
          break;

        case QUVI_SCRIPT_TYPE_SCAN:
          q->scripts.curr.scan = NULL;
          break;
        }
    }

  switch (type)
    {
    case QUVI_SCRIPT_TYPE_PLAYLIST:
      q->scripts.curr.playlist = (q->scripts.curr.playlist != NULL)
                                 ? g_slist_next(q->scripts.curr.playlist)
                                 : l;
      r = (q->scripts.curr.playlist != NULL)
          ? QUVI_TRUE
          : QUVI_FALSE;
      break;

    case QUVI_SCRIPT_TYPE_MEDIA:
    default:
      q->scripts.curr.media = (q->scripts.curr.media != NULL)
                              ? g_slist_next(q->scripts.curr.media)
                              : l;
      r = (q->scripts.curr.media != NULL)
          ? QUVI_TRUE
          : QUVI_FALSE;
      break;

    case QUVI_SCRIPT_TYPE_SCAN:
      q->scripts.curr.scan = (q->scripts.curr.scan != NULL)
                             ? g_slist_next(q->scripts.curr.scan)
                             : l;
      r = (q->scripts.curr.scan != NULL)
          ? QUVI_TRUE
          : QUVI_FALSE;
      break;
    }
  return (r);
}

#undef _W

/* vim: set ts=2 sw=2 tw=72 expandtab: */
