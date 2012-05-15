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

/** @file query_formats_new.c */

#include "config.h"

#include <glib.h>

#include "quvi.h"
/* -- */
#include "_quvi_s.h"
#include "_quvi_media_s.h"
#include "_quvi_query_formats_s.h"
/* -- */
#include "misc/match_media_script.h"

static gpointer _query_formats_new(gchar *fmts)
{
  _quvi_query_formats_t qf = g_new0(struct _quvi_query_formats_s, 1);
  gchar **r = g_strsplit(fmts, ",", 0);
  gint i = -1;

  while (r[++i] != NULL)
    qf->formats = g_slist_prepend(qf->formats, g_strdup(r[i]));

  qf->formats = g_slist_reverse(qf->formats);
  g_strfreev(r);
  r = NULL;

  return (qf);
}

/** @brief Query available media formats to an URL
@note @ref quvi_query_formats_free the handle when done using it
@sa @ref query_formats
@ingroup queryformats
*/
quvi_query_formats_t quvi_query_formats_new(quvi_t handle, const char *url)
{
  _quvi_query_formats_t qf = NULL;
  _quvi_t q = (_quvi_t) handle;
  _quvi_media_t m = NULL;
  gchar *fmts = NULL;

  /* If G_DISABLE_CHECKS is defined then the check is not performed. */
  g_return_val_if_fail(handle != NULL, NULL);
  g_return_val_if_fail(url != NULL, NULL);

  q->status.rc = m_match_media_script(q, &m, url,
                                      QM_MATCH_MS_QUERY_FORMATS,
                                      &fmts /* Must be g_free'd */);
  if (m != NULL)
    {
      quvi_media_free((quvi_media_t) m);
      m = NULL;

      qf = _query_formats_new(fmts);

      g_free(fmts);
      fmts = NULL;
    }

  return (qf);
}

/* vim: set ts=2 sw=2 tw=72 expandtab: */
