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

#ifndef qscript_h
#define qscript_h

/** @file qscript.h */

/** @cond NODOC */
#define QUVI_SCRIPT_PROPERTY_TYPE_STRING 0x100000
#define QUVI_SCRIPT_PROPERTY_TYPE_LONG   0x200000
#define QUVI_SCRIPT_PROPERTY_TYPE_DOUBLE 0x300000
#define QUVI_SCRIPT_PROPERTY_TYPE_VOID   0x400000
#define QUVI_SCRIPT_PROPERTY_MASK        0xf00000
/** @endcond */

/** @enum QuviScriptType */
typedef enum
{
  QUVI_SCRIPT_TYPE_PLAYLIST,
  QUVI_SCRIPT_TYPE_MEDIA,
  QUVI_SCRIPT_TYPE_SCAN
} QuviScriptType;

/** @enum QuviScriptProperty */
typedef enum
{
  QUVI_SCRIPT_PROPERTY_CATEGORIES =
  QUVI_SCRIPT_PROPERTY_TYPE_STRING+1, /**< Media script specific */
  QUVI_SCRIPT_PROPERTY_FILEPATH,
  QUVI_SCRIPT_PROPERTY_FILENAME,
  QUVI_SCRIPT_PROPERTY_DOMAIN,
  QUVI_SCRIPT_PROPERTY_SHA1,
  QUVI_SCRIPT_PROPERTY_SITE /**< Media script specific */
} QuviScriptProperty;

#endif /* qscript_h */

/* vim: set ts=2 sw=2 tw=72 expandtab: */
