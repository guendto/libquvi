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

#include "config.h"

#include <lauxlib.h>
#include <gcrypt.h>
#include <glib.h>
#include <quvi.h>

#include "_quvi_s.h"
/* -- */
#include "gcrypt/crypto.h"
#include "lua/quvi/crypto/opts.h"
#include "lua/quvi/crypto/err.h"
#include "lua/quvi/opts.h"
#include "lua/def.h"

static gboolean _chk_if_set(lua_State *l, GSList *opts, gboolean croak_flag,
                            const QuviObjectOption qoo, GSList **dst,
                            const gchar *w)
{
  const gboolean r = l_quvi_object_opts_is_set(opts, qoo, dst);
  if (croak_flag == TRUE && r == FALSE)
    luaL_error(l, "%s required", w);
  return (r);
}

#define _chk_req_as(qoo,what,dst,type)\
  do {\
    _chk_if_set(l, opts, TRUE, qoo, &p, what);\
    dst = ((l_quvi_object_opt_t) p->data)->value.type;\
  } while (0)

#define _chk_req_cb(n,what,cb)\
  do {\
    _chk_if_set(l, opts, TRUE, n, &p, what);\
    cb(l, co, p);\
  } while (0)

#define _chk_opt_as(qoo,dst,type)\
  do {\
    if (_chk_if_set(l, opts, FALSE, qoo, &p, NULL) == TRUE)\
      dst = ((l_quvi_object_opt_t) p->data)->value.type;\
  } while (0)

static void _chk_opts_given(lua_State *l, GSList *opts)
{
  if (opts == NULL)
    luaL_error(l, "expects a table of crypto options passed as an arg");
}

static void _chk_opts_common_req(lua_State *l, GSList *opts,
                                 l_quvi_object_crypto_opts_t co)
{
  GSList *p;

  _chk_req_as(QUVI_OBJECT_OPTION_CRYPTO_ALGORITHM,
              QOCO_ALGORITHM, co->algoname, str);
}

/* Encrypt and decrypt option checks. */
void l_quvi_object_crypto_chk_opts(lua_State *l, GSList *opts,
                                   l_quvi_object_crypto_opts_t co)
{
  GSList *p;

  _chk_opts_given(l, opts);
  _chk_opts_common_req(l, opts, co);

  /* required */

  _chk_req_as(QUVI_OBJECT_OPTION_CRYPTO_CIPHER_MODE,
              QOCO_CIPHER_MODE, co->cipher.mode, n);

  _chk_req_as(QUVI_OBJECT_OPTION_CRYPTO_CIPHER_KEY,
              QOCO_CIPHER_KEY, co->cipher.key, str);

  /* optional */

  _chk_opt_as(QUVI_OBJECT_OPTION_CRYPTO_CIPHER_FLAGS,
              co->cipher.flags, n);
}

/* Hash option checks. */
void l_quvi_object_crypto_hash_chk_opts(lua_State *l, GSList *opts,
                                        l_quvi_object_crypto_opts_t co)
{
  _chk_opts_given(l, opts);
  _chk_opts_common_req(l, opts, co);
}

/* vim: set ts=2 sw=2 tw=72 expandtab: */
