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

static gint _cmp(const gchar *a, const gchar *b, const gint o)
{
  gint r = g_strcmp0(a, b);
  if (o == QUVI_SCRIPT_SORT_ORDER_ASCEND)
    r = r>0;
  else if (o == QUVI_SCRIPT_SORT_ORDER_DESCEND)
    r = r<0;
  return (r);
}

/* Sort by whatever is set in the options. */
gint m_sort_scripts(gconstpointer a, gconstpointer b, gpointer p)
{
  const _quvi_script_t qsa = (_quvi_script_t) a;
  const _quvi_script_t qsb = (_quvi_script_t) b;
  const _quvi_t q = (_quvi_t) p;
  const QuviScriptSortOrder o = q->opt.scripts.sort_order;

  switch (q->opt.scripts.sort_by)
    {
      /* Media */
    case QUVI_SCRIPT_SORT_BY_CATEGORIES:
      return (_cmp(qsa->media.categories->str, qsb->media.categories->str, o));
    case QUVI_SCRIPT_SORT_BY_SITE:
      return (_cmp(qsa->media.site->str, qsb->media.site->str, o));
      /* Any */
    case QUVI_SCRIPT_SORT_BY_FILENAME:
      return (_cmp(qsa->fname->str, qsb->fname->str, o));
    case QUVI_SCRIPT_SORT_BY_FILEPATH:
      return (_cmp(qsa->fpath->str, qsb->fpath->str, o));
    case QUVI_SCRIPT_SORT_BY_DOMAIN:
      return (_cmp(qsa->domain->str, qsb->domain->str, o));
    case QUVI_SCRIPT_SORT_BY_SHA1:
      return (_cmp(qsa->sha1->str, qsb->sha1->str, o));
    default:
      break;
    }

  return (-1);
}

/* vim: set ts=2 sw=2 tw=72 expandtab: */
