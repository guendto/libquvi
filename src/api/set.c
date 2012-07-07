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

/** @file set.c */

#include "config.h"

#include <glib.h>

#include "quvi.h"
/* -- */
#include "_quvi_s.h"

static QuviError _set(_quvi_t q, QuviOption o, va_list arg)
{
  switch (o)
    {
    case QUVI_OPTION_MEDIA_SCRIPT_PROTOCOL_CATEGORY:
      q->opt.scripts.category = va_arg(arg, glong);
      break;
    case QUVI_OPTION_VERIFY_MEDIA_STREAM_URL:
      q->opt.verify = (gboolean) va_arg(arg, glong) >0;
      break;
    case QUVI_OPTION_REQUEST_FORMAT:
      g_string_assign(q->opt.format, va_arg(arg, gchar*));
      break;
    case QUVI_OPTION_AUTOPROXY:
      q->opt.autoproxy = (gboolean) va_arg(arg, glong) >0;
      break;

      /* Callback */

    case QUVI_OPTION_CALLBACK_STATUS:
      q->cb.status = va_arg(arg, quvi_callback_status);
      break;

      /* Default */

    default:
      return (QUVI_ERROR_INVALID_ARG);
    }
  return (QUVI_OK);
}

/** @brief Set library handle option
@sa @ref getting_started
@ingroup lib
*/
void quvi_set(quvi_t handle, QuviOption option, ...)
{
  _quvi_t q = (_quvi_t) handle;
  va_list arg;

  /* If G_DISABLE_CHECKS is defined then the check is not performed. */
  g_return_if_fail(handle != NULL);

  va_start(arg, option);
  q->status.rc = _set(handle, option, arg);
  va_end(arg);
}


/* vim: set ts=2 sw=2 tw=72 expandtab: */
