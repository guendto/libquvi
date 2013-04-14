/* libquvi
 * Copyright (C) 2012,2013  Toni Gundogdu <legatvs@gmail.com>
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

#ifndef n_def_h
#define n_def_h

/* These values are used with the quvi.fetch function. */

typedef enum
{
  QUVI_FETCH_OPTION_FROM_CHARSET,
  QUVI_FETCH_OPTION_USER_AGENT,
  QUVI_FETCH_OPTION_TYPE
} QuviFetchOption;

typedef enum
{
  QUVI_FETCH_TYPE_PLAYLIST,
  QUVI_FETCH_TYPE_CONFIG,
  QUVI_FETCH_TYPE_URL
} QuviFetchType;

#endif /* n_def_h */

/* vim: set ts=2 sw=2 tw=72 expandtab: */
