/* libquvi
 * Copyright (C) 2012  Toni Gundogdu <legatvs@gmail.com>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
 * 02110-1301  USA
 */

#include "config.h"

#include <glib.h>

#include "quvi.h"
/* -- */
#include "_quvi_s.h"

extern gchar *l_exec_util_resolve_redirections(_quvi_t, const gchar*);

/* Caller should always check the q->status.rc value after calling this. */
void m_resolve(_quvi_t q, const gchar *url, GString *dst)
{
  gchar *r = l_exec_util_resolve_redirections(q, url);
  g_assert(dst != NULL);
  if (r != NULL)
  {
    g_string_assign(dst, r);
    g_free(r);
    r = NULL;
  }
}

/* vim: set ts=2 sw=2 tw=72 expandtab: */
