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
#include <proxy.h>
#include <curl/curl.h>

#include "quvi.h"
/* -- */
#include "_quvi_s.h"

static void _set_proxy(_quvi_t q, const gchar *url)
{
  pxProxyFactory *pf = (pxProxyFactory*) q->handle.proxy;
  gchar **r = px_proxy_factory_get_proxies(pf, (gchar*) url);
  if (r != NULL)
    {
      gint i = 0;

      for (; r[i] != NULL; ++i)
        curl_easy_setopt(q->handle.curl, CURLOPT_PROXY, r[i]);

      g_strfreev(r);
      r = NULL;
    }
}

void c_autoproxy(_quvi_t q, const gchar *url)
{
  if (q->opt.autoproxy != QUVI_TRUE || q->handle.proxy == NULL)
    return;

  _set_proxy(q, url);
}

/* vim: set ts=2 sw=2 tw=72 expandtab: */
