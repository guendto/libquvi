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

#include "config.h"

#include <glib.h>

#include "quvi.h"
/* -- */
#include "_quvi_s.h"

/* Convenience function that wraps URL redirection check.
 * - Returns either new destination (must be freed) or NULL
 * - Honors the QUVI_OPTION_RESOLVE_URL_REDIRECTIONS
 * - Check quvi_ok after calling this function */
gchar *m_resolve(_quvi_t q, const gchar *url,
                 QuviBoolean ignore_noresolve_flag)
{
  quvi_resolve_t r = quvi_resolve_new(q, (gchar*) url, ignore_noresolve_flag);
  gchar *u = NULL;

  if (quvi_ok(q) == QUVI_TRUE)
    {
      if (quvi_resolve_forwarded(r) == QUVI_TRUE)
        u = g_strdup(quvi_resolve_destination_url(r));
    }

  quvi_resolve_free(r);
  r = NULL;

  return (u);
}

/* vim: set ts=2 sw=2 tw=72 expandtab: */
