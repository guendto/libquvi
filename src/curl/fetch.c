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
#include "_quvi_media_s.h"
#include "_quvi_net_s.h"
#include "_quvi_net_opt_s.h"
/* -- */
#include "curl/autoproxy.h"
#include "curl/temp.h"
#include "net/def.h"

static void _set_opt(gpointer p, gpointer userdata)
{
  _quvi_net_opt_t o;
  CURL *c;

  o = (_quvi_net_opt_t) p;
  c = userdata;

  switch ((glong) o->id)
    {
    case QUVI_FETCH_OPTION_USER_AGENT:
      curl_easy_setopt(c, CURLOPT_USERAGENT, o->value.s->str);
      break;
    case QUVI_FETCH_OPTION_COOKIE:
      curl_easy_setopt(c, CURLOPT_COOKIE, o->value.s->str);
      break;
    default:
      break;
    }
}

static void _set_opts(_quvi_net_t n, _c_temp_t t, CURL *c)
{
  typedef curl_write_callback cwc;

  curl_easy_setopt(c, CURLOPT_WRITEFUNCTION, (cwc) c_temp_wrcb);
  curl_easy_setopt(c, CURLOPT_URL, n->url.addr->str);
  curl_easy_setopt(c, CURLOPT_WRITEDATA, t);
  /* CURLOPT_ENCODING -> CURLOPT_ACCEPT_ENCODING 7.21.6+ */
  curl_easy_setopt(c, CURLOPT_ENCODING, "");
  /* Set cURL options from script fetch args (if any), e.g. user-agent */
  g_slist_foreach(n->options, _set_opt, c);

  c_autoproxy(n->handle.quvi, n->url.addr->str);
}

static void _reset_opts(CURL *c)
{
  curl_easy_setopt(c, CURLOPT_WRITEFUNCTION, NULL);
  curl_easy_setopt(c, CURLOPT_WRITEDATA, NULL);
}

static QuviError _fetch(_quvi_net_t n, CURL *c)
{
  CURLcode curlcode;
  QuviError rc;

  curlcode = curl_easy_perform(c);
  curl_easy_getinfo(c, CURLINFO_RESPONSE_CODE, &n->status.resp_code);

  rc = QUVI_OK;

  if (curlcode == CURLE_OK && n->status.resp_code == 200)
    ;
  else
    {
      if (curlcode == CURLE_OK)
        {
#define _EOK "server responded with code %03ld"
          g_string_printf(n->status.errmsg, _EOK, n->status.resp_code);
#undef _EOK
        }
      else
        {
          const gchar *s = curl_easy_strerror(curlcode);
          const glong c = n->status.resp_code;
          const gint cc = curlcode;
#define _ENO "%s (HTTP/%03ld, cURL=0x%03x)"
          g_string_printf(n->status.errmsg, _ENO, s, c, cc);
#undef _ENO
        }
      rc = QUVI_ERROR_CALLBACK;
    }
  return (rc);
}

QuviError c_fetch(_quvi_net_t n)
{
  QuviError rc;
  _c_temp_t t;
  CURL *c;

  c = n->handle.quvi->handle.curl;
  t = c_temp_new();

  _set_opts(n, t, c);
  rc = _fetch(n, c);
  _reset_opts(c);

  if (rc == QUVI_OK)
    g_string_assign(n->fetch.content, t->p);

  c_temp_free(t);
  t = NULL;

  return (rc);
}

/* vim: set ts=2 sw=2 tw=72 expandtab: */
