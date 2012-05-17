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
  /** Default: QUVI_OPTION_MEDIA_SCRIPT_PROTOCOL_CATEGORY_ALL */
  QUVI_OPTION_MEDIA_SCRIPT_PROTOCOL_CATEGORY,
  /** Resolve URL redirections, e.g. "shortned URLs" before passing them
   * to the media scripts. Default: QUVI_TRUE */
  QUVI_OPTION_RESOLVE_URL_REDIRECTIONS,
  /** This setting applies to HTTP media stream URLs only. Additionally,
   * this causes the library parse the HTTP content-type and content-length
   * fields which would otherwise remain unset.  Default: QUVI_TRUE
   * @note Negates @ref QUVI_SUPPORTS_MODE_ONLINE */
  QUVI_OPTION_VERIFY_MEDIA_STREAM_URL,
  /** Default: QUVI_SCRIPT_SORT_ORDER_ASCEND */
  QUVI_OPTION_SCRIPT_SORT_ORDER,
  /** Default: QUVI_SCRIPT_SORT_ORDER_BY_FILEPATH */
  QUVI_OPTION_SCRIPT_SORT_BY,
  /** Default: None */
  QUVI_OPTION_CALLBACK_STATUS,
  /** Tells the media script(s) to get the requested format if available.
   * Default: "default", can be "best" which causes the media script to
   * try to pick the best available format for the media.
   * @note
   *  - This option should be set only after @ref query_formats
   *  - Available formats may vary greatly depending on the website
   */
  QUVI_OPTION_REQUEST_FORMAT
} QuviOption;

#endif /* qoption_h */

/* vim: set ts=2 sw=2 tw=72 expandtab: */
