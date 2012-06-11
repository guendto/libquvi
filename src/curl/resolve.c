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

#include <curl/curl.h>
#include <glib.h>

#include "quvi.h"
/* -- */
#include "_quvi_s.h"
#include "_quvi_net_resolve_s.h"

/* Set cURL options. */
static void _set_opts(_quvi_net_resolve_t r, CURL *c)
{
  curl_easy_setopt(c, CURLOPT_URL, r->url.addr->str);
  /* Use HEAD request: we're only interested in the header metadata. */
  curl_easy_setopt(c, CURLOPT_NOBODY, 1L); /* GET -> HEAD. */
}

static void _reset_opts(CURL *c)
{
  curl_easy_setopt(c, CURLOPT_HTTPGET, 1L); /* HEAD -> GET. */
}

/* Check whether the server returned a redirection URL. */
static QuviError _chk_redir(_quvi_net_resolve_t r, CURL *c)
{
  gint curlcode = curl_easy_perform(c);
  QuviError rc = QUVI_OK;

  curl_easy_getinfo(c, CURLINFO_RESPONSE_CODE, &r->status.resp_code);

  if (curlcode == CURLE_OK && r->status.resp_code == 200)
    {
      gchar *u = NULL;
      curl_easy_getinfo(c, CURLINFO_EFFECTIVE_URL, &u);

      if (g_strcmp0(r->url.addr->str, u) != 0)
        g_string_assign(r->url.dst, u);

      rc = QUVI_OK;
    }
  else
    {
      if (curlcode == CURLE_OK)
        {
#define _EOK "server responded with code %03ld"
          g_string_printf(r->status.errmsg, _EOK, r->status.resp_code);
#undef _EOK
        }
      else
        {
          const gchar *s = curl_easy_strerror(curlcode);
          const glong rc = r->status.resp_code;
          const gint cc = curlcode;
#define _ENO "%s (HTTP/%03ld, cURL=0x%03x)"
          g_string_printf(r->status.errmsg, _ENO, s, rc, cc);
#undef _ENO
        }
      rc = QUVI_ERROR_CALLBACK;
    }
  return (rc);
}

/* Resolve an URL redirection if needed. */
QuviError c_resolve(_quvi_t q, _quvi_net_resolve_t r)
{
  CURL *c = q->handle.curl;
  QuviError rc = QUVI_OK;

  _set_opts(r, c);
  rc = _chk_redir(r, c);
  _reset_opts(c);

  return (rc);
}

/* vim: set ts=2 sw=2 tw=72 expandtab: */
