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

#ifndef qsupp_h
#define qsupp_h

/** @file qsupp.h */

/** @enum QuviSupportsMode */
typedef enum
{
  QUVI_SUPPORTS_MODE_OFFLINE, /**< Networkless check */
  QUVI_SUPPORTS_MODE_ONLINE   /**< Resolve URL prior to check */
} QuviSupportsMode;

/** @enum QuviSupportsType */
typedef enum
{
  QUVI_SUPPORTS_TYPE_PLAYLIST = 0x1,
  QUVI_SUPPORTS_TYPE_MEDIA = 0x2,
  QUVI_SUPPORTS_TYPE_ANY =
  (QUVI_SUPPORTS_TYPE_PLAYLIST
   |QUVI_SUPPORTS_TYPE_MEDIA)
} QuviSupportsType;

#endif /* qsupp_h */

/* vim: set ts=2 sw=2 tw=72 expandtab: */
