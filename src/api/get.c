/* libquvi
 * Copyright (C) 2012  Toni Gundogdu <legatvs@gmail.com>
 *
 * This file is part of libquvi <http://quvi.sourceforge.net/>.
 *
 * This library is free software: you can redistribute it and/or
 * modify it under the terms of the GNU Affero General Public
 * License as published by the Free Software Foundation, either
 * version 3 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General
 * Public License along with this library.  If not, see
 * <http://www.gnu.org/licenses/>.
 */

/** @file get.c */

#include "config.h"

#include <glib.h>

#include "quvi.h"
/* -- */
#include "_quvi_s.h"

static void _get(_quvi_t q, QuviInfo info, ...)
{
  gpointer *vp;
  va_list arg;
  glong *lp;
  gint type;
#ifdef _CURRENTLY_UNUSED
  gdouble *dp;
  gchar **sp;
#endif

  va_start(arg, info);
  type = QUVI_INFO_TYPE_MASK & (gint) info;

  vp = NULL;
  lp = NULL;
#ifdef _CURRENTLY_UNUSED
  dp = NULL;
  sp = NULL;
#endif

  switch (type)
    {
    case QUVI_INFO_TYPE_LONG:
      lp = va_arg(arg, glong*);
      break;
    case QUVI_INFO_TYPE_VOID:
      vp = va_arg(arg, gpointer*);
      break;
#ifdef _CURRENTLY_UNUSED
    case QUVI_INFO_TYPE_DOUBLE:
      dp = va_arg(arg, gdouble*);
      break;
    case QUVI_INFO_TYPE_STRING:
      sp = va_arg(arg, gchar**);
      break;
#endif
    default:
      break;
    }
  va_end(arg);

  switch (info)
    {
    case QUVI_INFO_RESPONSE_CODE:
    default:
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
    }
}

/** @brief Return information about the library handle
@sa @ref getting_started
@ingroup lib
*/
void quvi_get(quvi_t handle, QuviInfo info, ...)
{
  va_list arg;
  gpointer p;

  /* If G_DISABLE_CHECKS is defined then the check is not performed. */
  g_return_if_fail(handle != NULL);

  va_start(arg, info);
  p = va_arg(arg, gpointer);
  va_end(arg);

  _get((_quvi_t) handle, info, p);
}

/* vim: set ts=2 sw=2 tw=72 expandtab: */
