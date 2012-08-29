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

#include "config.h"

#include <glib.h>
#include <quvi.h>

static void fetch(const quvi_word type, const gpointer p)
{
  switch (type)
    {
    default:
      g_printerr("[%s] Fetch %s ...", __func__, (gchar*) p);
      break;
    case QUVI_CALLBACK_STATUS_FETCH_CONFIG:
      g_printerr("[%s] Fetch config ...", __func__);
      break;
    case QUVI_CALLBACK_STATUS_FETCH_PLAYLIST:
      g_printerr("[%s] Fetch playlist ...", __func__);
      break;
    case QUVI_CALLBACK_STATUS_DONE:
      g_printerr("done.\n");
      break;
    }
}

static void resolve(const quvi_word type)
{
  if (type == QUVI_CALLBACK_STATUS_DONE)
    g_printerr("done.\n");
  else
    g_printerr("[%s] Check for URL redirection ...", __func__);
}

static void verify(const quvi_word type)
{
  if (type == QUVI_CALLBACK_STATUS_DONE)
    g_printerr("done.\n");
  else
    g_printerr("[%s] Verify URL ...", __func__);
}

QuviError status(glong param, gpointer p)
{
  const quvi_word status = quvi_loword(param);
  const quvi_word type = quvi_hiword(param);

  switch (status)
    {
    case QUVI_CALLBACK_STATUS_RESOLVE:
      resolve(type);
      break;
    case QUVI_CALLBACK_STATUS_FETCH:
      fetch(type, p);
      break;
    case QUVI_CALLBACK_STATUS_VERIFY:
      verify(type);
      break;
    }
  return (QUVI_OK);
}

/* vim: set ts=2 sw=2 tw=72 expandtab: */
