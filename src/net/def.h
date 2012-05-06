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

#ifndef n_def_h
#define n_def_h

/*
 * Network options set in media scripts, e.g.:
 * function parse(t)
 *   local foo = quvi.fetch(URL, {user_agent='bar/1.0'})
 * end
 */
#define MSO_ARBITRARY_COOKIE  "arbitrary_cookie"
#define MSO_FROM_CHARSET      "from_charset"
#define MSO_USER_AGENT        "user_agent"

/* Status types for fetch callback. */
#define FETCH_TYPE      "type"
#define FETCH_PAGE      "page"
#define FETCH_CONFIG    "config"
#define FETCH_PLAYLIST  "playlist"

#endif /* n_def_h */

/* vim: set ts=2 sw=2 tw=72 expandtab: */
