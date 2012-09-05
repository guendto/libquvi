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

#ifndef examples_h
#define examples_h

extern quvi_playlist_t qp;
extern quvi_resolve_t qr;
extern quvi_verify_t qv;
extern quvi_media_t qm;
extern quvi_scan_t qs;
extern quvi_t q;

QuviError examples_status(glong param, gpointer p);
void examples_enable_autoproxy();
void examples_enable_verbose();
void examples_exit_if_error();
void examples_cleanup();

gboolean examples_chk_val_sv(gchar**, gchar**, gchar**);
gboolean examples_chk_val_s(gchar*, gchar**, gchar**);

#endif /* examples_h */

/* vim: set ts=2 sw=2 tw=72 expandtab: */
