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

/** @file errmsg.c */

#include "config.h"

#include <glib.h>

#include "quvi.h"
/* -- */
#include "_quvi_s.h"

static const gchar *msg[] =
{
  "No error",
  "Aborted by callback",
  "'playlist scripts' not found in the path",
  "'media scripts' not found in the path",
  "'scan scripts' not found in the path",
  "'utility scripts' not found in the path",
  "Invalid argument to function",
  "cURL initialization failed",
  "Lua initialization failed"
};

static const gchar inv_code_msg[] = "Invalid error code";

/** @return NULL-terminated error string
@note Do not attempt to free the returned string
@sa @ref getting_started
@ingroup convenience
*/
const char *quvi_errmsg(quvi_t handle)
{
  _quvi_t q = (_quvi_t) handle;
  const gchar *s = msg[0];
  QuviError n = QUVI_OK;
  gint i = 1;

  if (handle == NULL)
    return ((gchar*) msg[QUVI_ERROR_INVALID_ARG]);

  for (n = q->status.rc; msg[i] != NULL; ++i);

  if ((gint) n<0 || n>i)
    {
      if (q->status.errmsg->len >0)
        s = q->status.errmsg->str;
      else
        s = inv_code_msg;
    }
  else
    s = msg[n];

  return (s);
}

/* vim: set ts=2 sw=2 tw=72 expandtab: */
