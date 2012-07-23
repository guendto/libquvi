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

/** @file verify_get.c */

#include "config.h"

#include <glib.h>

#include "quvi.h"
/* -- */
#include "_quvi_s.h"
#include "_quvi_verify_s.h"

static QuviError _verify_get(_quvi_verify_t v, QuviVerifyProperty n, ...)
{
  QuviError rc;
  gdouble *dp;
  va_list arg;
  gchar **sp;
  gint type;

  va_start(arg, n);
  type = QUVI_VERIFY_PROPERTY_TYPE_MASK & (gint) n;

  dp = NULL;
  sp = NULL;

  rc = QUVI_OK;

  switch (type)
    {
    case QUVI_VERIFY_PROPERTY_TYPE_STRING:
      sp = va_arg(arg, gchar**);
      if (sp == NULL)
        rc = QUVI_ERROR_INVALID_ARG;
      break;
    case QUVI_VERIFY_PROPERTY_TYPE_DOUBLE:
      dp = va_arg(arg, gdouble*);
      if (dp == NULL)
        rc = QUVI_ERROR_INVALID_ARG;
      break;
    default:
      rc = QUVI_ERROR_INVALID_ARG;
      break;
    }
  va_end(arg);

  if (rc != QUVI_OK)
    return (rc);

  switch (n)
    {
    case QUVI_VERIFY_PROPERTY_FILE_EXTENSION:
      *sp = v->file_ext->str;
      break;
    case QUVI_VERIFY_PROPERTY_LENGTH_BYTES:
      *dp = v->length_bytes;
      break;
    case QUVI_VERIFY_PROPERTY_CONTENT_TYPE:
      *sp = v->content_type->str;
      break;
    default:
      rc = QUVI_ERROR_INVALID_ARG;
      break;
    }
  return (rc);
}

/** @brief Return a verify property
@sa @ref verify_url
@ingroup verify
*/
void quvi_verify_get(quvi_verify_t handle, QuviVerifyProperty property, ...)
{
  _quvi_verify_t v;
  va_list arg;
  gpointer p;
  _quvi_t q;

  /* If G_DISABLE_CHECKS is defined then the check is not performed. */
  g_return_if_fail(handle != NULL);

  va_start(arg, property);
  p = va_arg(arg, gpointer);
  va_end(arg);

  v = (_quvi_verify_t) handle;
  q = v->handle.quvi;

  q->status.rc = _verify_get(v, property, p);
}

/* vim: set ts=2 sw=2 tw=72 expandtab: */
