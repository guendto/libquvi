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

/** @file resolve_new.c */

#include "config.h"

#include <glib.h>

#include "quvi.h"
/* -- */
#include "_quvi_s.h"
#include "_quvi_net_resolve_s.h"
/* -- */
#include "misc/resolve.h"
#include "net/resolve.h"
#include "net/handle.h"

/** @brief Resolve URL redirection
@note @ref quvi_resolve_free the handle when done using it
@ingroup resolve
*/
quvi_resolve_t quvi_resolve_new(quvi_t handle, const char *url)
{
  _quvi_t q = (_quvi_t) handle;
  _quvi_net_resolve_t r = NULL;

  /* If G_DISABLE_CHECKS is defined then the check is not performed. */
  g_return_val_if_fail(handle != NULL, NULL);
  g_return_val_if_fail(url != NULL, NULL);

  r = n_resolve_new(q, url);
  m_resolve(q, url, r->url.dst);

  return (r);
}

/* vim: set ts=2 sw=2 tw=72 expandtab: */
