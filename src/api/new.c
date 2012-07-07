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

/** @file new.c */

#include "config.h"

#include <string.h>
#include <proxy.h>
#include <glib.h>

#include "quvi.h"
/* -- */
#include "_quvi_s.h"

static gpointer _quvi_new()
{
  _quvi_t q = g_new0(struct _quvi_s, 1);
  q->opt.scripts.category = QUVI_MEDIA_SCRIPT_PROTOCOL_CATEGORY_ALL;
  q->opt.format = g_string_new("default");
  q->status.errmsg = g_string_new(NULL);
  q->opt.verify = TRUE;
  return (q);
}

/** @cond NODOC */
extern QuviError m_scan_scripts(_quvi_t q);
extern QuviError l_init(_quvi_t q);
extern QuviError c_init(_quvi_t q);
/** @endcond */

/** @brief Create a new library handle
@sa @ref getting_started
@ingroup lib
*/
quvi_t quvi_new()
{
  _quvi_t q = _quvi_new();

  q->status.rc = l_init(q);

  if (q->status.rc == QUVI_OK)
    q->status.rc = m_scan_scripts(q);

  if (q->status.rc == QUVI_OK)
    q->status.rc = c_init(q);

  if (q->status.rc == QUVI_OK)
    {
      q->handle.proxy = px_proxy_factory_new();
      if (q->handle.proxy == NULL)
        q->status.rc = QUVI_ERROR_PROXY_INIT;
    }

  if (q->status.rc == QUVI_OK)
    {
      const gchar *v = g_getenv("LIBQUVI_VERBOSE_SCRIPTS");
      if (v != NULL && strlen(v) >0)
        q->opt.scripts.verbose = TRUE;
    }

  return (q);
}

/* vim: set ts=2 sw=2 tw=72 expandtab: */
