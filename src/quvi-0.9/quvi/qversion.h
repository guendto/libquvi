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

#ifndef qversion_h
#define qversion_h

/** @file qversion.h */

/** @enum QuviVersion */
typedef enum
{
  QUVI_VERSION,
  QUVI_VERSION_BUILD_TARGET,
  QUVI_VERSION_BUILD_TIME,
  QUVI_VERSION_SCRIPTS  /**< libquvi-scripts version */
} QuviVersion;

#endif /* qversion_h */

/* vim: set ts=2 sw=2 tw=72 expandtab: */
