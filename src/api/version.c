/* libquvi
 * Copyright (C) 2012  Toni Gundogdu <legatvs@gmail.com>
 *
 * This file is part of libquvi <http://quvi.sourceforge.net/>.
 *
 * This library is free software: you can redistribute it and/or
 * modify it under the terms of the GNU Affero General Public
 * License as published by the Free Software Foundation, either
 * version 3 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General
 * Public License along with this library.  If not, see
 * <http://www.gnu.org/licenses/>.
 */

/** @file version.c */

#include "config.h"

#include <string.h>
#include <glib.h>

#include "quvi.h"
/* -- */
#include "_quvi_s.h"

static const gchar *_version[] =
{
#ifdef VN
  VN
#else
  PACKAGE_VERSION
#endif
  , BUILD_OPTS,
  CANONICAL_TARGET,
  BUILD_TIME
};

static gchar version_scripts[32];

static const gchar *read_scripts_version()
{
  gchar *c = NULL;
  if (g_file_get_contents(VERSIONFILE, &c, NULL, NULL) == TRUE)
    {
      gchar *s = g_strescape(g_strstrip(c), NULL);
      g_snprintf(version_scripts, sizeof(version_scripts), "%s", s);

      g_free(s);
      s = NULL;

      g_free(c);
      c = NULL;
    }
  else
    version_scripts[0] = '\0';
  return (version_scripts);
}

/** @return NULL-terminated version string
@note Do not attempt to free the returned string
@ingroup convenience
*/
const char *quvi_version(QuviVersion version)
{
  switch (version)
    {
    case QUVI_VERSION_SCRIPTS:
      return (read_scripts_version());

    case QUVI_VERSION_CONFIGURATION:
    case QUVI_VERSION_BUILD_TARGET:
    case QUVI_VERSION_BUILD_TIME:
      return (_version[version]);

    default:
      break;
    }
  return (_version[QUVI_VERSION]);
}

/* vim: set ts=2 sw=2 tw=72 expandtab: */
