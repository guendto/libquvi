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

#ifndef qerror_h
#define qerror_h

/** @file qerror.h */

/** @enum QuviError */
typedef enum
{
  QUVI_OK,
  QUVI_ERROR_CALLBACK_ABORTED, /**< Aborted by callback */
  QUVI_ERROR_NO_PLAYLIST_SCRIPTS,
  QUVI_ERROR_NO_MEDIA_SCRIPTS,
  QUVI_ERROR_NO_SCAN_SCRIPTS,
  QUVI_ERROR_NO_UTIL_SCRIPTS,
  QUVI_ERROR_INVALID_ARG,
  QUVI_ERROR_PROXY_INIT,
  QUVI_ERROR_CURL_INIT,
  QUVI_ERROR_LUA_INIT,
  QUVI_ERROR_NO_STREAM_ID_CROAK = 0x40,
  QUVI_ERROR_NO_SUPPORT,
  QUVI_ERROR_CALLBACK,
  /**< Error occurred in callback, this could be either a network error
   * (network callback function returned an error) or a status callback
   * function returned an error. */
  QUVI_ERROR_SCRIPT
} QuviError;

#endif /* qerror_h */

/* vim: set ts=2 sw=2 tw=72 expandtab: */
