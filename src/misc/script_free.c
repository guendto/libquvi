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

#include "config.h"

#include <glib.h>

#include "quvi.h"
/* -- */
#include "_quvi_s.h"
#include "_quvi_script_s.h"
#include "_quvi_util_script_s.h"
/* -- */
#include "misc/script_free.h"

void m_script_free(gpointer p, gpointer userdata)
{
  _quvi_script_t qs = (_quvi_script_t) p;

  if (p == NULL)
    return;

  /* Media */

  g_string_free(qs->media.categories, TRUE);
  qs->media.categories = NULL;

  g_string_free(qs->media.site, TRUE);
  qs->media.site = NULL;

  /* Any */

  g_string_free(qs->fpath, TRUE);
  qs->fpath = NULL;

  g_string_free(qs->fname, TRUE);
  qs->fname = NULL;

  g_string_free(qs->domain, TRUE);
  qs->domain = NULL;

  g_string_free(qs->sha1, TRUE);
  qs->sha1 = NULL;

  g_free(p);
  p = NULL;
}

void m_util_script_free(gpointer p, gpointer userdata)
{
  _quvi_util_script_t us = (_quvi_util_script_t) p;

  if (p == NULL)
    return;

  g_string_free(us->fpath, TRUE);
  us->fpath = NULL;

  g_string_free(us->fname, TRUE);
  us->fname = NULL;

  g_string_free(us->sha1, TRUE);
  us->sha1 = NULL;

  g_free(p);
  p = NULL;
}

/* vim: set ts=2 sw=2 tw=72 expandtab: */
