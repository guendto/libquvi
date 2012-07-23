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

/** @file verify_new.c */

#include "config.h"

#include <glib.h>

#include "quvi.h"
/* -- */
#include "_quvi_s.h"
#include "_quvi_verify_s.h"

static gpointer _verify_new(_quvi_t q, const gchar *url)
{
  _quvi_verify_t qv = g_new0(struct _quvi_verify_s, 1);
  qv->content_type = g_string_new(NULL);
  qv->file_ext = g_string_new(NULL);
  qv->url.input = g_string_new(url);
  qv->handle.quvi = q;
  return (qv);
}

/** @cond NODOC */
QuviError n_verify(_quvi_verify_t);
/** @endcond */

/** @brief Verify URL
@return New handle, @ref quvi_verify_free if when done using it
@note Use @ref_quvi_ok for checking if an error occurred
@ingroup verify
*/
quvi_verify_t quvi_verify_new(quvi_t handle, const char *url)
{
  _quvi_verify_t v;
  _quvi_t q;

  /* If G_DISABLE_CHECKS is defined then the check is not performed. */
  g_return_val_if_fail(handle != NULL, NULL);
  g_return_val_if_fail(url != NULL, NULL);

  q = (_quvi_t) handle;
  v = _verify_new(q, url);

  q->status.rc = n_verify(v);

  return (v);
}

/* vim: set ts=2 sw=2 tw=72 expandtab: */
