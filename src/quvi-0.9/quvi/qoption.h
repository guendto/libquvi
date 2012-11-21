/* libquvi
 * Copyright (C) 2012  Toni Gundogdu <legatvs@gmail.com>
 *
 * This file is part of libquvi <http://quvi.sourceforge.net/>.
 *
 * This library is free software: you can redistribute it and/or
 * modify it under the terms of the GNU Affero General Public
 * License as published by the Free Software Foundation, either
 * version 3 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General
 * Public License along with this library.  If not, see
 * <http://www.gnu.org/licenses/>.
 */

#ifndef qoption_h
#define qoption_h

/** @file qoption.h */

/** @enum QuviOption
@brief Options to be used with @ref quvi_set */
typedef enum
{
  /** Default: None */
  QUVI_OPTION_CALLBACK_STATUS,
  /** Autodetect and set the proxy for new connections.
   * Default: QUVI_FALSE. When enabled (QUVI_TRUE), libquvi uses libproxy
   * to detect the system proxy settings and sets the CURLOPT_PROXY to the
   * libproxy returned value. This is done for each new connection.
   * @sa http://curl.haxx.se/libcurl/c/curl_easy_setopt.html#CURLOPTPROXY
   * @sa http://libproxy.googlecode.com/
   */
  QUVI_OPTION_AUTOPROXY
} QuviOption;

#endif /* qoption_h */

/* vim: set ts=2 sw=2 tw=72 expandtab: */
