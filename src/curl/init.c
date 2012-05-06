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

QuviError c_init(_quvi_t q)
{
  curl_global_init(CURL_GLOBAL_ALL);

  q->handle.curl = curl_easy_init();
  if (q->handle.curl == NULL)
    return (QUVI_ERROR_CURL_INIT);

  curl_easy_setopt(q->handle.curl, CURLOPT_USERAGENT, "Mozilla/5.0");
  curl_easy_setopt(q->handle.curl, CURLOPT_FOLLOWLOCATION, 1L);
  curl_easy_setopt(q->handle.curl, CURLOPT_NOBODY, 0L);

  return (QUVI_OK);
}

/* vim: set ts=2 sw=2 tw=72 expandtab: */
