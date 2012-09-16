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

/** @file media_stream_select.c */

#include "config.h"

#include <glib/gi18n-lib.h>
#include <glib.h>

#include "quvi.h"
/* -- */
#include "_quvi_s.h"
#include "_quvi_media_s.h"
/* -- */
#include "misc/re.h"

static QuviError _select(_quvi_media_t qm, const gchar *id)
{
  gboolean found_flag;
  QuviError rc;
  _quvi_t q;
  gchar **r;
  gint i;

  quvi_media_stream_reset(qm);
  q = qm->handle.quvi;

  r = g_strsplit(id, ",", 0);
  found_flag = FALSE;
  rc = QUVI_OK;

  for (i=0; r[i] != NULL && found_flag == FALSE; ++i)
    {
      if (g_strcmp0(r[i], "croak") == 0)
        {
          static const gchar *_E =
            N_("Could not match any available media stream IDs to `%s'; \
operation aborted by the \"croak\" keyword");

          g_string_printf(q->status.errmsg,
                          g_dgettext(GETTEXT_PACKAGE, _E),
                          id);

          rc = QUVI_ERROR_NO_STREAM_ID_CROAK;
          break;
        }
      else if (g_strcmp0(r[i], "best") == 0)
        {
          quvi_media_stream_choose_best(qm);
          break;
        }
      else
        {
          _quvi_media_stream_t qms;

          while (quvi_media_stream_next(qm) == TRUE)
            {
              qms = (_quvi_media_stream_t) qm->curr.stream->data;

              found_flag = m_match(qms->id->str, r[i]);
              if (found_flag == TRUE)
                break;
            }

          if (found_flag == FALSE) /* Use the first stream as a fallback. */
            quvi_media_stream_reset(qm);
        }
    }
  g_strfreev(r);
  r = NULL;

  return (rc);
}

/** @brief Select a @ref m_stream matching a @ref m_stream_id

Matches the @ref m_stream_id (pattern) to the available media stream
IDs and selects the stream if the IDs matched. The function returns
immediately if the IDs matched. The ID value may be a
comma-separated value (e.g. "foo,bar,baz"). The ID value may
contain the keywords 'croak' and 'best' (see notes below).
@note
  - ID value is used as a regular expression pattern
    - The only exception to this is when it contains a comma-separated
      list of patterns
  - ID may contain the keywords 'best' and 'croak'
    - These are reserved keywords used by both the library and the
      scripts
    - The function returns immediately after reaching either
    - 'croak' will cause the function register an error when the
      keyword is reached by the function
      - The error may be checked with @ref quvi_ok and returned with
        either @ref quvi_get (for code) and @ref quvi_errmsg
    - 'best' is identical to calling @ref quvi_media_stream_choose_best
  - If nothing matched (and the 'croak' keyword was not specified) the
    function falls back to the first available stream (the default)
  - Always check the result with @ref quvi_ok
@sa @ref parse_media
@ingroup mediaprop
*/
void quvi_media_stream_select(quvi_media_t handle, const char *id)
{
  _quvi_media_t qm;
  _quvi_t q;

  qm = (_quvi_media_t) handle;
  q = qm->handle.quvi;

  /* If G_DISABLE_CHECKS is defined then the check is not performed. */
  g_return_if_fail(handle != NULL);

  q->status.rc = _select(qm, id);
}

/* vim: set ts=2 sw=2 tw=72 expandtab: */
