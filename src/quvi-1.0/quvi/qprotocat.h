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

#ifndef qprotocat_h
#define qprotocat_h

/** @file qprotocat.h */

/** @enum QuviMediaScriptProtocolCategory */
typedef enum
{
  QUVI_MEDIA_SCRIPT_PROTOCOL_CATEGORY_HTTP = 0x1,
  QUVI_MEDIA_SCRIPT_PROTOCOL_CATEGORY_MMS  = 0x2,
  QUVI_MEDIA_SCRIPT_PROTOCOL_CATEGORY_RTSP = 0x4,
  QUVI_MEDIA_SCRIPT_PROTOCOL_CATEGORY_RTMP = 0x8,
  QUVI_MEDIA_SCRIPT_PROTOCOL_CATEGORY_RTMPE = 0x10,
  QUVI_MEDIA_SCRIPT_PROTOCOL_CATEGORY_ALL =
  (QUVI_MEDIA_SCRIPT_PROTOCOL_CATEGORY_HTTP
  |QUVI_MEDIA_SCRIPT_PROTOCOL_CATEGORY_MMS
  |QUVI_MEDIA_SCRIPT_PROTOCOL_CATEGORY_RTSP
  |QUVI_MEDIA_SCRIPT_PROTOCOL_CATEGORY_RTMP
  |QUVI_MEDIA_SCRIPT_PROTOCOL_CATEGORY_RTMPE)
} QuviMediaScriptProtocolCategory;

#endif /* qprotocat_h */

/* vim: set ts=2 sw=2 tw=72 expandtab: */
