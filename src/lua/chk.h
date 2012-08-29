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

#ifndef l_chk_h
#define l_chk_h

gboolean l_chk_accepts(lua_State*, _quvi_script_t, const gchar*,
                       const gchar*, const gchar*);

gboolean l_chk_assign_s(lua_State*, const gchar*, GString*);
gboolean l_chk_s(lua_State*, const gchar*, gchar**);

gboolean l_chk_assign_n(lua_State*, const gchar*, gdouble*);
gboolean l_chk_n(lua_State*, const gchar*, gdouble*);

gboolean l_chk_assign_b(lua_State*, const gchar*, gboolean*);
gboolean l_chk_b(lua_State*, const gchar*, gboolean*);

#endif /* l_chk_h */

/* vim: set ts=2 sw=2 tw=72 expandtab: */
