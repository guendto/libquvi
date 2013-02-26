/* libquvi
 * Copyright (C) 2013  Toni Gundogdu <legatvs@gmail.com>
 *
 * This file is part of libquvi <http://quvi.sourceforge.net/>.
 *
 * This program is free software: you can redistribute it and/or
 * modify it under the terms of the GNU Affero General Public
 * License as published by the Free Software Foundation, either
 * version 3 of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General
 * Public License along with this program.  If not, see
 * <http://www.gnu.org/licenses/>.
 */

#ifndef l_quvi_opts_h
#define l_quvi_opts_h

typedef enum
{
  QUVI_OBJECT_OPTION_CROAK_IF_ERROR     = 0x01,
  /* fetch */
  QUVI_OBJECT_OPTION_FETCH_FROM_CHARSET = 0x20,
  /* http */
  QUVI_OBJECT_OPTION_HTTP_USER_AGENT    = 0x40,
  /* crypto */
  QUVI_OBJECT_OPTION_CRYPTO_CIPHER_FLAGS = 0x60,
  QUVI_OBJECT_OPTION_CRYPTO_CIPHER_MODE,
  QUVI_OBJECT_OPTION_CRYPTO_CIPHER_KEY,
  QUVI_OBJECT_OPTION_CRYPTO_ALGORITHM
} QuviObjectOption;

struct l_quvi_object_opt_s
{
  struct
  {
    gchar *str;
    gdouble n;
  } value;
  gdouble id;
};

typedef struct l_quvi_object_opt_s *l_quvi_object_opt_t;

GSList *l_quvi_object_opts_new(lua_State*, gint);
void l_quvi_object_opts_free(GSList*);

gboolean l_quvi_object_opts_is_set(GSList*, QuviObjectOption, GSList**);
void l_quvi_object_opts_curl(GSList*, _quvi_t);

gboolean l_quvi_object_opts_croak_if_error(GSList*);

#endif /* l_quvi_opts_h */

/* vim: set ts=2 sw=2 tw=72 expandtab: */
