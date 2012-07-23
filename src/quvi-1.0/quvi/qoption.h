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

#ifndef qoption_h
#define qoption_h

/** @file qoption.h */

/** @enum QuviOption
@brief Options to be used with @ref quvi_set */
typedef enum
{
  /** Determines which of the media scripts of the protocol categories
   * should be included when the library looks up the media scripts
   * from the search paths.
   *
   * Normally, if an application could handle only some of the protocols,
   * e.g. HTTP, it should set this option appropriately (e.g.
   * QUVI_MEDIA_SCRIPT_PROTOCOL_CATEGORY_HTTP) to limit the media script
   * support to those websites that return media stream URLs suitable to the
   * application.
   *
   * Default: QUVI_MEDIA_SCRIPT_PROTOCOL_CATEGORY_ALL.
   *
   * @sa QuviMediaScriptProtocolCategory
   * @sa @ref proto_cat */
  QUVI_OPTION_MEDIA_SCRIPT_PROTOCOL_CATEGORY,
  /** Default: None */
  QUVI_OPTION_CALLBACK_STATUS,
  /** Tells the media script(s) to get the requested format if available.
   * Default: "default", can be "best" which causes the media script to
   * try to pick the best available format for the media.
   * @note
   *  - This option should be set only after @ref query_formats
   *  - Available formats may vary greatly depending on the website
   *  - The value may be a comma-separated list of format strings
   * @section comma_sep_list Comma-separated list of format strings
   *
   * Example values:
   *
   * @li "foo,bar,croak" - Unless either 'foo' or 'bar' is matched, exit
   * with an error
   * @li "foo,best" - Choose the 'best' available format (whatever the
   * script deems this to be), unless 'foo' is matched
   * @li "foo,bar" - Choose whatever script deems to be the default,
   * unless either 'foo' or 'bar' is matched first
   *
   * @sa @ref query_formats
   */
  QUVI_OPTION_REQUEST_FORMAT,
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
