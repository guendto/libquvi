/* libquvi
 * Copyright (C) 2012  Toni Gundogdu <legatvs@gmail.com>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
 * 02110-1301  USA
 */

#ifndef qverifyprop_h
#define qverifyprop_h

/** @file qverifyprop.h */

/** @cond NODOC */
#define QUVI_VERIFY_PROPERTY_TYPE_STRING 0x100000
#define QUVI_VERIFY_PROPERTY_TYPE_LONG   0x200000
#define QUVI_VERIFY_PROPERTY_TYPE_DOUBLE 0x300000
#define QUVI_VERIFY_PROPERTY_TYPE_VOID   0x400000
#define QUVI_VERIFY_PROPERTY_TYPE_MASK   0xf00000
/** @endcond */

/** @enum QuviVerifyProperty */
typedef enum
{
  /* string */
  QUVI_VERIFY_PROPERTY_FILE_EXTENSION = QUVI_VERIFY_PROPERTY_TYPE_STRING+1,
  QUVI_VERIFY_PROPERTY_CONTENT_TYPE,
  /* double */
  QUVI_VERIFY_PROPERTY_LENGTH_BYTES =
  ((QUVI_VERIFY_PROPERTY_CONTENT_TYPE - QUVI_VERIFY_PROPERTY_TYPE_STRING)
  + QUVI_VERIFY_PROPERTY_TYPE_DOUBLE + 0x20)
} QuviVerifyProperty;

#endif /* qverifyprop_h */

/* vim: set ts=2 sw=2 tw=72 expandtab: */
