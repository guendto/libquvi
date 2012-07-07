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

#ifndef examples_h
#define examples_h

extern quvi_query_formats_t qqf;
extern quvi_playlist_t qp;
extern quvi_resolve_t qr;
extern quvi_media_t qm;
extern quvi_scan_t qs;
extern quvi_t q;

QuviError status(glong param, gpointer p);
void enable_autoproxy();
void enable_verbose();
void exit_if_error();
void cleanup();

#endif /* examples_h */

/* vim: set ts=2 sw=2 tw=72 expandtab: */
