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

#include <string.h>
#include <glib.h>

#include "quvi.h"
/* -- */
#include "_quvi_s.h"
#include "_quvi_media_s.h"
#include "_quvi_playlist_s.h"
#include "_quvi_script_s.h"
/* -- */
#include "misc/script_free.h"
#include "misc/playlist.h"
#include "misc/media.h"
#include "misc/re.h"
#include "lua/exec.h"

/* Return path to script file. */
static GString *_get_fpath(const gchar *path, const gchar *fname)
{
  GString *r;
  gchar *s;

  s = g_build_filename(path, fname, NULL);
  r = g_string_new(s);

  g_free(s);
  s = NULL;

  return (r);
}

/* Return SHA1 for script file. */
static GString *_file_sha1(const GString *c)
{
  GString *r = g_string_new(NULL);
  if (c != NULL)
    {
      gchar *s = g_compute_checksum_for_string(G_CHECKSUM_SHA1, c->str, -1);
      g_string_assign(r, s);
      g_free(s);
      s = NULL;
    }
  return (r);
}

/* Return file contents in a GString. */
static GString *_contents(GString *fpath)
{
  gchar *c = NULL;
  g_file_get_contents(fpath->str, &c, NULL, NULL);
  if (c != NULL)
    {
      GString *s = g_string_new(c);
      g_free(c);
      c = NULL;
      return (s);
    }
  return (NULL);
}

static const gchar *scripts_dir = NULL;
static const gchar *show_script = NULL;
static const gchar *show_dir = NULL;

typedef QuviError (*exec_script_ident_callback)(gpointer, GSList*);
typedef gpointer (*new_ident_callback)(_quvi_t, const gchar*);
typedef void (*free_ident_callback)(gpointer);

/* Parses the values returned by the ident function. */
static void _chk_script_ident(_quvi_t q, _quvi_script_t qs, gboolean *ok,
                              new_ident_callback cb_new,
                              exec_script_ident_callback cb_exec,
                              free_ident_callback cb_free)
{
  static const gchar URL[] = "http://foo";

  QuviError rc;
  gpointer p;
  GSList *s;

  p = cb_new(q, URL);
  s = NULL;
  s = g_slist_prepend(s, qs);
  rc = cb_exec(p, s);

  cb_free(p);
  p = NULL;

  g_slist_free(s);
  s = NULL;

  /* Script ident function should return "no support". If anything else
   * is returned, there's something wrong with the script. */
  if (rc == QUVI_ERROR_NO_SUPPORT)
    *ok = TRUE;
  else
    {
      g_critical("[%s] %s", __func__, q->status.errmsg->str);
      *ok = FALSE;
    }
}

/* Check if a pattern matches in a string. */
static gboolean _chk(const gchar *s, const gchar *p)
{
  const gboolean r = m_match(s, p);
  if (show_script != NULL && strlen(show_script) >0)
    {
      if (r == FALSE)
        g_message("[%s] no match: `%s'", __func__, p);
    }
  return (r);
}

/* New script */
static gpointer script_new(const gchar *fpath, const gchar *fname,
                           const GString *c)
{
  _quvi_script_t qs = g_new0(struct _quvi_script_s, 1);
  qs->domains = g_string_new(NULL);
  qs->fpath = g_string_new(fpath);
  qs->fname = g_string_new(fname);
  qs->sha1 = _file_sha1(c);
  return (qs);
}

/* New media script. */
static gpointer _new_media_script(_quvi_t q, const gchar *path,
                                  const gchar *fname)
{
  _quvi_script_t qs;
  GString *fpath;
  GString *c;

  fpath = _get_fpath(path, fname);
  c = _contents(fpath);
  qs = NULL;

  if (c != NULL)
    {
      gboolean OK =
        (_chk(c->str, "^\\-\\-\\s+libquvi\\-scripts") == TRUE
         && _chk(c->str, "^function ident") == TRUE
         && _chk(c->str, "^function query_formats") == TRUE
         && _chk(c->str, "^function parse") == TRUE);

      if (OK == TRUE)
        {
          typedef free_ident_callback fic;

          qs = script_new(fpath->str, fname, c);

          _chk_script_ident(q, qs, &OK, m_media_new,
                            l_exec_media_script_ident,
                            (fic) m_media_free);
        }

      g_string_free(c, TRUE);
      c = NULL;

      if (OK == FALSE)
        {
          m_script_free(qs, NULL);
          qs = NULL;
        }
    }

  if (fpath != NULL)
    {
      g_string_free(fpath, TRUE);
      fpath = NULL;
    }

  return (qs);
}

/* New playlist script. */
static gpointer _new_playlist_script(_quvi_t q, const gchar *path,
                                     const gchar *fname)
{
  _quvi_script_t qs;
  GString *fpath;
  GString *c;

  fpath = _get_fpath(path, fname);
  c = _contents(fpath);
  qs = NULL;

  if (c != NULL)
    {
      gboolean OK =
        (_chk(c->str, "^\\-\\-\\s+libquvi\\-scripts") == TRUE
         && _chk(c->str, "^function ident") == TRUE
         && _chk(c->str, "^function parse") == TRUE);

      if (OK == TRUE)
        {
          typedef free_ident_callback fic;

          qs = script_new(fpath->str, fname, c);

          _chk_script_ident(q, qs, &OK, m_playlist_new,
                            l_exec_playlist_script_ident,
                            (fic) m_playlist_free);
        }

      g_string_free(c, TRUE);
      c = NULL;

      if (OK == FALSE)
        {
          m_script_free(qs, NULL);
          qs = NULL;
        }
    }

  if (fpath != NULL)
    {
      g_string_free(fpath, TRUE);
      fpath = NULL;
    }

  return (qs);
}

/* New scan script. */
static gpointer _new_scan_script(_quvi_t q, const gchar *path,
                                 const gchar *fname)
{
  _quvi_script_t qs;
  GString *fpath;
  GString *c;

  fpath = _get_fpath(path, fname);
  c = _contents(fpath);
  qs = NULL;

  if (c != NULL)
    {
      gboolean OK =
        (_chk(c->str, "^\\-\\-\\s+libquvi\\-scripts") == TRUE
         && _chk(c->str, "^function parse") == TRUE);

      if (OK == TRUE)
        qs = script_new(fpath->str, fname, c);

      g_string_free(c, TRUE);
      c = NULL;

      if (OK == FALSE)
        {
          m_script_free(qs, NULL);
          qs = NULL;
        }
    }

  if (fpath != NULL)
    {
      g_string_free(fpath, TRUE);
      fpath = NULL;
    }

  return (qs);
}

/* New utility script. */
static gpointer _new_util_script(_quvi_t q, const gchar *path,
                                 const gchar *fname)
{
  _quvi_script_t qs;
  GString *fpath;
  GString *c;

  fpath = _get_fpath(path, fname);
  c = _contents(fpath);
  qs = NULL;

  if (c != NULL)
    {
      const gboolean OK =
        (_chk(c->str, "^\\-\\-\\s+libquvi\\-scripts") == TRUE);

      if (OK == TRUE)
        qs = script_new(fpath->str, fname, c);

      g_string_free(c, TRUE);
      c = NULL;

      if (OK == FALSE)
        {
          m_script_free(qs, NULL);
          qs = NULL;
        }
    }

  if (fpath != NULL)
    {
      g_string_free(fpath, TRUE);
      fpath = NULL;
    }

  return (qs);
}

/* Check for duplicate script. */
static gboolean _chkdup_script(_quvi_t q, gpointer script, GSList *l)
{
  _quvi_script_t a, b;
  GSList *curr;

  a = (_quvi_script_t) script;
  curr = l;

  while (curr != NULL)
    {
      b = (_quvi_script_t) curr->data;

      if (g_string_equal(a->sha1, b->sha1) == TRUE)
        return (TRUE);

      curr = g_slist_next(curr);
    }
  return (FALSE);
}

/* Include '*.lua' files only. */
static gint _lua_files_only(const gchar *fpath)
{
  const gchar *ext = strrchr(fpath, '.');
  return (fpath[0] != '.' && ext != NULL && strcmp(ext, ".lua") == 0);
}

/* Sort scripts alphabetically by filepath. */
static gint _sort(gconstpointer a, gconstpointer b)
{
  const _quvi_script_t qsa = (_quvi_script_t) a;
  const _quvi_script_t qsb = (_quvi_script_t) b;
  return (g_strcmp0(qsa->fpath->str, qsb->fpath->str) >0);
}

typedef gpointer (*new_script_callback)(_quvi_t, const gchar*, const gchar*);
typedef gboolean (*chkdup_script_callback)(_quvi_t, gpointer, GSList*);
typedef void (*free_script_callback)(gpointer, gpointer);

static gboolean _glob_scripts_dir(_quvi_t q, const gchar *path, GSList **dst,
                                  new_script_callback cb_new,
                                  free_script_callback cb_free,
                                  chkdup_script_callback cb_chkdup)
{
  const gchar *fname;
  GDir *dir;

  if (show_dir != NULL && strlen(show_dir) >0)
    g_message("libquvi: %s: %s", __func__, path);

  dir = g_dir_open(path, 0, NULL);
  if (dir == NULL)
    return (FALSE);

  while ((fname = g_dir_read_name(dir)) != NULL)
    {
      if (_lua_files_only(fname) != 0)
        {
          gpointer s = cb_new(q, path, fname);
          if (s == NULL)
            {
              /* Either file read failed or this is not a valid
               * libquvi-script. */
              if (show_script != NULL && strlen(show_script) >0)
                {
                  g_message("libquvi: %s: rejected: %s [INVALID]",
                            __func__, fname);
                }
            }
          else
            {
              /* Valid libquvi-script file. */
              const gboolean r = cb_chkdup(q, s, *dst);

              if (r == FALSE)
                *dst = g_slist_prepend(*dst, s);
              else
                {
                  cb_free(s, NULL);
                  s = NULL;
                }

              if (show_script != NULL && strlen(show_script) >0)
                {
                  g_message("libquvi: %s: %s: %s [%s]",
                            __func__,
                            (r == FALSE) ? "accepted" : "rejected",
                            fname,
                            (r == FALSE) ? "OK" : "DUPLICATE");
                }
            }
        }
    }
  g_dir_close(dir);
  dir = NULL;

  if (*dst != NULL)
    *dst = g_slist_sort(*dst, _sort);

  return (*dst != NULL);
}

typedef enum
{
  GLOB_PLAYLIST_SCRIPTS,
  GLOB_MEDIA_SCRIPTS,
  GLOB_SCAN_SCRIPTS,
  GLOB_UTIL_SCRIPTS
} GlobMode;

static const gchar *dir[] =
{
  "lua/playlist/",
  "lua/media/",
  "lua/scan/",
  "lua/util/",
  NULL
};

static gboolean _glob_scripts(_quvi_t q, const GlobMode m, GSList **dst)
{
  chkdup_script_callback cb_chkdup;
  free_script_callback cb_free;
  new_script_callback cb_new;
  gchar *path;

  cb_new = NULL;
  *dst = NULL;

  switch (m)
    {
    case GLOB_PLAYLIST_SCRIPTS:
      cb_new = _new_playlist_script;
      break;
    case GLOB_MEDIA_SCRIPTS:
      cb_new = _new_media_script;
      break;
    case GLOB_SCAN_SCRIPTS:
      cb_new = _new_scan_script;
      break;
    case GLOB_UTIL_SCRIPTS:
      cb_new = _new_util_script;
      break;
    default:
      g_error("%s: %d: invalid mode", __func__, __LINE__);
    }

  cb_chkdup = _chkdup_script;
  cb_free = m_script_free;

  {
    /* LIBQUVI_SCRIPTS_DIR (excl.) */

    if (scripts_dir != NULL && strlen(scripts_dir) >0)
      {
        gboolean r = FALSE;

        path = g_build_path(G_DIR_SEPARATOR_S, scripts_dir, dir[m], NULL);
        r = _glob_scripts_dir(q, path, dst, cb_new, cb_free, cb_chkdup);

        g_free(path);
        path = NULL;

        return (r);
      }
  }

  {
    /* Current working directory. */

    gchar *cwd = g_get_current_dir();
    path = g_build_path(G_DIR_SEPARATOR_S, cwd, dir[m], NULL);

    g_free(cwd);
    cwd = NULL;

    _glob_scripts_dir(q, path, dst, cb_new, cb_free, cb_chkdup);

    g_free(path);
    path = NULL;
  }

#ifdef SCRIPTSDIR
  {
    /* SCRIPTSDIR from config.h */

    path = g_build_path(G_DIR_SEPARATOR_S, SCRIPTSDIR, dir[m], NULL);
    _glob_scripts_dir(q, path, dst, cb_new, cb_free, cb_chkdup);

    g_free(path);
    path = NULL;
  }
#endif /* SCRIPTSDIR */

  return (*dst != NULL);
}

static gboolean dir_exists(const gchar *path)
{
  GDir *dir = g_dir_open(path, 0, NULL);

  if (dir == NULL)
    return (FALSE);

  g_dir_close(dir);
  dir = NULL;

  return (TRUE);
}

extern void l_modify_pkgpath(_quvi_t, const gchar*);

#define Q_COMMON_DIR "lua/common"

/* Check for "lua/common/" directory, append it to "package.path" if
 * found. The library ignores the contents of the directory. */
static void chk_common_scripts(_quvi_t q)
{
  gchar *path;

  {
    /* LIBQUVI_SCRIPTS_DIR (excl.) */

    if (scripts_dir != NULL && strlen(scripts_dir) >0)
      {
        path = g_build_path(G_DIR_SEPARATOR_S,
                            scripts_dir, Q_COMMON_DIR, NULL);

        if (dir_exists(path) == TRUE)
          l_modify_pkgpath(q, path);

        g_free(path);
        path = NULL;

        return;
      }
  }

  {
    /* Current working directory. */

    gchar *cwd = g_get_current_dir();
    path = g_build_path(G_DIR_SEPARATOR_S, cwd, Q_COMMON_DIR, NULL);

    if (dir_exists(path) == TRUE)
      l_modify_pkgpath(q, path);

    g_free(path);
    path = NULL;

    g_free(cwd);
    cwd = NULL;
  }

#ifdef SCRIPTSDIR
  {
    /* SCRIPTSDIR from config.h */

    path = g_build_path(G_DIR_SEPARATOR_S, SCRIPTSDIR, Q_COMMON_DIR, NULL);

    if (dir_exists(path) == TRUE)
      l_modify_pkgpath(q, path);

    g_free(path);
    path = NULL;
  }
#endif /* SCRIPTSDIR */
}

#undef Q_COMMON_DIR

QuviError m_scan_scripts(_quvi_t q)
{
  QuviError rc;

  scripts_dir = g_getenv("LIBQUVI_SCRIPTS_DIR");
  show_script = g_getenv("LIBQUVI_SHOW_SCRIPT");
  show_dir = g_getenv("LIBQUVI_SHOW_DIR");

  chk_common_scripts(q); /* Ignore what lua/common/ holds. */

  rc = _glob_scripts(q, GLOB_UTIL_SCRIPTS, &q->scripts.util)
       ? QUVI_OK
       : QUVI_ERROR_NO_UTIL_SCRIPTS;

  if (rc == QUVI_OK)
    {
      rc = _glob_scripts(q, GLOB_MEDIA_SCRIPTS, &q->scripts.media)
           ? QUVI_OK
           : QUVI_ERROR_NO_MEDIA_SCRIPTS;
    }

  if (rc == QUVI_OK)
    {
      rc = _glob_scripts(q, GLOB_PLAYLIST_SCRIPTS, &q->scripts.playlist)
           ? QUVI_OK
           : QUVI_ERROR_NO_PLAYLIST_SCRIPTS;
    }

  if (rc == QUVI_OK)
    {
      rc = _glob_scripts(q, GLOB_SCAN_SCRIPTS, &q->scripts.scan)
           ? QUVI_OK
           : QUVI_ERROR_NO_SCAN_SCRIPTS;
    }

  return (rc);
}

/* vim: set ts=2 sw=2 tw=72 expandtab: */
