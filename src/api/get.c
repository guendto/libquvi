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

/** @file get.c */

#include "config.h"

#include <glib.h>

#include "quvi.h"
/* -- */
#include "_quvi_s.h"

static void _get(_quvi_t q, QuviInfo info, ...)
{
  gpointer *vp = NULL;
  gdouble *dp = NULL;
  gchar **sp = NULL;
  glong *lp = NULL;
  gint type = 0;
  va_list arg;

  va_start(arg, info);
  type = QUVI_INFO_TYPE_MASK & (gint) info;

  switch (type)
    {
    case QUVI_INFO_TYPE_DOUBLE:
      dp = va_arg(arg, gdouble*);
      break;
    case QUVI_INFO_TYPE_STRING:
      sp = va_arg(arg, gchar**);
      break;
    case QUVI_INFO_TYPE_LONG:
      lp = va_arg(arg, glong*);
      break;
    case QUVI_INFO_TYPE_VOID:
      vp = va_arg(arg, gpointer*);
      break;
    default:
      break;
    }
  va_end(arg);

  switch (info)
    {
    case QUVI_INFO_RESPONSE_CODE:
      if (lp != NULL)
        *lp = q->status.resp_code;
      break;
    case QUVI_INFO_ERROR_CODE:
      if (lp != NULL)
        *lp = q->status.rc;
      break;
    case QUVI_INFO_CURL_HANDLE:
      if (vp != NULL)
        *vp = q->handle.curl;
      break;
    default:
      break;
    }
}

/** @brief Return information about the library handle
@sa @ref getting_started
@ingroup lib
*/
void quvi_get(quvi_t handle, QuviInfo info, ...)
{
  _quvi_t q = (_quvi_t) handle;
  gpointer p = NULL;
  va_list arg;

  /* If G_DISABLE_CHECKS is defined then the check is not performed. */
  g_return_if_fail(handle != NULL);

  va_start(arg, info);
  p = va_arg(arg, gpointer);
  va_end(arg);

  _get(q, info, p);
}

/* vim: set ts=2 sw=2 tw=72 expandtab: */
