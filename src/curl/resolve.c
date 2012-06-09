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
/* -- */
#include "curl/temp.h"

/* Set cURL options. */
static void _set_opts(_quvi_net_resolve_t r, _c_temp_t t, CURL *c)
{
  typedef curl_write_callback cwc;

  curl_easy_setopt(c, CURLOPT_WRITEFUNCTION, (cwc) c_temp_wrcb); /* tmp.c */
  curl_easy_setopt(c, CURLOPT_URL, r->url.addr->str);
  curl_easy_setopt(c, CURLOPT_FOLLOWLOCATION, 0L);
#ifdef SET_MAXREDIRS
  /* Set it to -1 for an infinite number of redirects (which is the
   * default). -- http://is.gd/kFsvE4 */
  curl_easy_setopt(c, CURLOPT_MAXREDIRS, -1);
#endif
  curl_easy_setopt(c, CURLOPT_WRITEDATA, t);
}

static void _reset_opts(CURL *c)
{
  curl_easy_setopt(c, CURLOPT_FOLLOWLOCATION, 1L);
  curl_easy_setopt(c, CURLOPT_HTTPGET, 1L);
}

/* Check whether the server returned a redirection URL. */
static QuviError _chk_redir(_quvi_net_resolve_t r, CURL *c)
{
  gint curlcode = curl_easy_perform(c);
  QuviError rc = QUVI_OK;

  curl_easy_getinfo(c, CURLINFO_RESPONSE_CODE, &r->status.resp_code);

  if (curlcode == CURLE_OK)
    {
      if (r->status.resp_code >= 301 && r->status.resp_code <= 303)
        {
          gchar *s = NULL;
          curl_easy_getinfo(c, CURLINFO_REDIRECT_URL, &s);
          g_string_assign(r->url.dst, s);
        }
    }
  else
    {
      g_string_printf(r->status.errmsg, "%s (HTTP/%03ld, cURL=0x%03x)",
                      curl_easy_strerror(curlcode),
                      r->status.resp_code,
                      curlcode);
      rc = QUVI_ERROR_CALLBACK;
    }
  return (rc);
}

/* Resolve an URL redirection if needed. */
QuviError c_resolve(_quvi_t q, _quvi_net_resolve_t r)
{
  _c_temp_t t = c_temp_new();
  CURL *c = q->handle.curl;
  QuviError rc = QUVI_OK;

  _set_opts(r, t, c);
  rc = _chk_redir(r, c);
  _reset_opts(c);

  c_temp_free(t);
  t = NULL;

  return (rc);
}

/* vim: set ts=2 sw=2 tw=72 expandtab: */
