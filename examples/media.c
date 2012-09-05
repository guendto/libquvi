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

#include <locale.h>
#include <stdlib.h>
#include <string.h>
#include <glib.h>
#include <quvi.h>

#include "examples.h"

struct _opts_s
{
  gboolean autoproxy;
  gboolean verbose;
  gchar **category;
  gboolean best;
  gchar *stream;
  gchar **url;
};

static struct _opts_s opts;

static const GOptionEntry entries[] =
{
  {
    "category", 'c', 0, G_OPTION_ARG_STRING_ARRAY, &opts.category,
    "Select media script protocol category", "CATEGORY"
  },
  {
    "stream", 's', 0, G_OPTION_ARG_STRING, &opts.stream,
    "Select stream ID, or a comma-separated list of IDs", "ID"
  },
  {
    "best", 'b', 0, G_OPTION_ARG_NONE, &opts.best,
    "Choose the best available stream, negates --stream", NULL
  },
  {
    "autoproxy", 'a', 0, G_OPTION_ARG_NONE, &opts.autoproxy,
    "Enable the autoproxy feature", NULL
  },
  {
    "verbose", 'v', 0, G_OPTION_ARG_NONE, &opts.verbose,
    "Verbose libcurl output", NULL
  },
  {
    G_OPTION_REMAINING, 0, 0, G_OPTION_ARG_STRING_ARRAY, &opts.url, "URL"
  },
  {NULL, 0, 0, 0, NULL, NULL, NULL}
};

struct _categ_lookup_s
{
  QuviMediaScriptProtocolCategory to;
  const gchar *from;
};

static const struct _categ_lookup_s categ_conv[] =
{
  /* http */
  {QUVI_MEDIA_SCRIPT_PROTOCOL_CATEGORY_HTTPS, "https"},
  {QUVI_MEDIA_SCRIPT_PROTOCOL_CATEGORY_HTTP,  "http"},
  /* rtmp */
  {QUVI_MEDIA_SCRIPT_PROTOCOL_CATEGORY_RTMPT, "rtmpt"},
  {QUVI_MEDIA_SCRIPT_PROTOCOL_CATEGORY_RTMPS, "rtmps"},
  {QUVI_MEDIA_SCRIPT_PROTOCOL_CATEGORY_RTMPE, "rtmpe"},
  {QUVI_MEDIA_SCRIPT_PROTOCOL_CATEGORY_RTMP,  "rtmp"},
  /* Other */
  {QUVI_MEDIA_SCRIPT_PROTOCOL_CATEGORY_RTSP, "rtsp"},
  {QUVI_MEDIA_SCRIPT_PROTOCOL_CATEGORY_MMS,  "mms"},
  {QUVI_MEDIA_SCRIPT_PROTOCOL_CATEGORY_ANY,  "any"},
  {0, NULL}
};

/* Return numerical value of the --category. */
static QuviMediaScriptProtocolCategory category_n()
{
  QuviMediaScriptProtocolCategory r;
  gint i,j;

  for (i=0, r=0; opts.category[i] != NULL; ++i)
    {
      for (j=0; categ_conv[j].from != NULL; ++j)
        {
          if (g_strcmp0(categ_conv[j].from, opts.category[i]) == 0)
            {
              r |= categ_conv[j].to;
              break;
            }
        }
    }
  return (r);
}

/* Return a string array containing accepted values for --category. */
static gchar **category_sv()
{
  gchar **r;
  gint i,j;

  i=0;
  while (categ_conv[i].from != NULL) ++i;
  r = g_new(gchar*, i+1);

  i=j=0;
  while (categ_conv[j].from != NULL)
    r[i++] = g_strdup(categ_conv[j++].from);
  r[i] = NULL;

  return (r);
}

static gboolean chk_category_values()
{
  gchar **v, *s;
  gboolean r;

  v = category_sv();
  r = examples_chk_val_sv(opts.category, v, &s);
  if (r == FALSE)
    {
      g_printerr(
        "error: invalid value (`%s') for the option `--category'\n", s);
    }

  g_strfreev(v);
  v = NULL;

  return (r);
}

static void dump_stream()
{
  gchar *url, *id;

  quvi_media_get(qm, QUVI_MEDIA_STREAM_PROPERTY_URL, &url);
  quvi_media_get(qm, QUVI_MEDIA_STREAM_PROPERTY_ID, &id);

  g_print("  id='%s', url='%s'\n", id, url);
}

static void dump_streams()
{
  while (quvi_media_stream_next(qm) == QUVI_TRUE)
    dump_stream();
}

static gint opts_new(gint argc, gchar **argv)
{
  GOptionContext *c;
  GOptionGroup *g;
  GError *e;
  gint r;

  c = g_option_context_new("URL");
  r = EXIT_SUCCESS;
  g = NULL;
  e = NULL;

  g_option_context_set_help_enabled(c, TRUE);
  g_option_context_add_main_entries(c, entries, NULL);

  if (g_option_context_parse(c, &argc, &argv, &e) == FALSE)
    {
      g_printerr("error: %s\n", e->message);
      g_error_free(e);
      r = EXIT_FAILURE;
      e = NULL;
    }

  g_option_context_free(c);
  c = NULL;

  /* Set the defaults. */

  if (opts.category == NULL)
    {
      gchar *v[] = {"any", NULL};
      opts.category = g_strdupv(v);
    }

  /* Check input. */

  if (chk_category_values() == FALSE)
    return (EXIT_FAILURE);

  if (opts.url == NULL)
    {
      g_printerr("error: no input URL\n");
      return (EXIT_FAILURE);
    }

  return (r);
}

static void opts_free()
{
  g_strfreev(opts.category);
  opts.category = NULL;

  g_free(opts.stream);
  opts.stream = NULL;

  g_strfreev(opts.url);
  opts.url = NULL;
}

typedef quvi_callback_status qcs;

gint main(gint argc, gchar **argv)
{
  QuviMediaScriptProtocolCategory category;
  gint i,r;
  gchar *s;

  g_assert(qm == NULL);
  g_assert(q == NULL);

  memset(&opts, 0, sizeof(struct _opts_s));
  setlocale(LC_ALL, "");

  r = opts_new(argc, argv);
  if (r != EXIT_SUCCESS)
    return (r);

  q = quvi_new();
  examples_exit_if_error();

  if (opts.autoproxy == TRUE)
    examples_enable_autoproxy();

  if (opts.verbose == TRUE)
    examples_enable_verbose();

  category = category_n();
  quvi_set(q, QUVI_OPTION_MEDIA_SCRIPT_PROTOCOL_CATEGORY, category);
  quvi_set(q, QUVI_OPTION_CALLBACK_STATUS, (qcs) examples_status);
  {
    gchar *s = g_strjoinv(",", opts.category);
    g_printerr("[%s] category=%s (0x%x)\n", __func__, s, category);
    g_free(s);
    s = NULL;
  }

  for (i=0; opts.url[i] != NULL; ++i)
    {
      qm = quvi_media_new(q, opts.url[i]);
      examples_exit_if_error();

      quvi_media_get(qm, QUVI_MEDIA_PROPERTY_TITLE, &s);
      g_print("[%s]\n  title='%s'\n", __func__, s);

      if (opts.best == TRUE)
        {
          quvi_media_stream_choose_best(qm);
          dump_stream();
        }
      else if (opts.stream != NULL)
        {
          quvi_media_stream_select(qm, opts.stream);
          examples_exit_if_error();
          dump_stream();
        }
      else
        dump_streams();

      quvi_media_free(qm);
      qm = NULL;
    }

  opts_free();
  examples_cleanup();

  g_assert(qm == NULL);
  g_assert(q == NULL);

  return (r);
}

/* vim: set ts=2 sw=2 tw=72 expandtab: */
