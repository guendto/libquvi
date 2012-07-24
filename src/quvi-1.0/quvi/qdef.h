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

#ifndef qdef_h
#define qdef_h

/** @file qdef.h */

typedef int (*quvi_callback_status)(long,void*); /**< Status callback type */

typedef void *quvi_playlist_t; /**< Playlist script type */
typedef void *quvi_resolve_t; /**< Resolve type */
typedef void *quvi_media_t; /**< Media type */
typedef void *quvi_scan_t; /**< Scan type */
typedef void *quvi_t; /**< Library handle type */

typedef uint32_t quvi_word; /**< Word type */
typedef uint8_t quvi_byte; /**< Byte type */

#define quvi_lobyte(w) ((quvi_byte)((uint64_t)(w) & 0xff)) /**< Return low byte */
#define quvi_hibyte(w) ((quvi_byte)((uint64_t)(w) >> 8)) /**< Return high byte */
#define quvi_loword(l) ((quvi_word)((uint64_t)(l) & 0xffff)) /**< Return low word */
#define quvi_hiword(l) ((quvi_word)((uint64_t)(l) >> 16)) /**< Return high word */

#endif /* qdef_h */

/* vim: set ts=2 sw=2 tw=72 expandtab: */
