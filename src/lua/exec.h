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

#ifndef l_exec_h
#define l_exec_h

QuviError l_exec_media_script_query_formats(gpointer, GSList*, gchar**);
QuviError l_exec_media_script_ident(gpointer, GSList*);
QuviError l_exec_media_script_parse(gpointer, GSList*);

QuviError l_exec_playlist_script_ident(gpointer, GSList*);
QuviError l_exec_playlist_script_parse(gpointer, GSList*);

QuviError l_exec_scan_script_parse(gpointer, gpointer, const gchar*);

#endif /* l_exec_h */

/* vim: set ts=2 sw=2 tw=72 expandtab: */
