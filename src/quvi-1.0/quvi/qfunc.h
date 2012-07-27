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

#ifndef qfunc_h
#define qfunc_h

#ifdef __cplusplus
extern "C" {
#endif

  quvi_t quvi_new();
  void quvi_free(quvi_t);

  void quvi_set(quvi_t, QuviOption, ...);
  void quvi_get(quvi_t, QuviInfo, ...);

  /* Script */

  QuviBoolean quvi_script_next(quvi_t, QuviScriptType);
  void quvi_script_get(quvi_t, QuviScriptType, QuviScriptProperty, ...);

  /* Media */

  quvi_media_t quvi_media_new(quvi_t, const char*);
  void quvi_media_free(quvi_media_t);

  void quvi_media_get(quvi_media_t, QuviMediaProperty, ...);

  QuviBoolean quvi_media_stream_next(quvi_media_t);
  void quvi_media_stream_reset(quvi_media_t);

  /* Query formats */

  quvi_query_formats_t quvi_query_formats_new(quvi_t, const char*);
  void quvi_query_formats_free(quvi_query_formats_t);

  const char *quvi_query_formats_get(quvi_query_formats_t);

  /* Playlist */

  quvi_playlist_t quvi_playlist_new(quvi_t, const char*);
  void quvi_playlist_free(quvi_playlist_t);

  void quvi_playlist_get(quvi_playlist_t, QuviPlaylistProperty, ...);
  QuviBoolean quvi_playlist_next_media_url(quvi_playlist_t);

  /* Scan */

  quvi_scan_t quvi_scan_new(quvi_t, const char*);
  void quvi_scan_free(quvi_scan_t);

  const char *quvi_scan_next_media_url(quvi_scan_t);

  /* Resolve */

  quvi_resolve_t quvi_resolve_new(quvi_t, const char*);
  void quvi_resolve_free(quvi_resolve_t);

  QuviBoolean quvi_resolve_forwarded(quvi_resolve_t);
  const char *quvi_resolve_destination_url(quvi_resolve_t);

  /* Verify */

  quvi_verify_t quvi_verify_new(quvi_t, const char*);
  void quvi_verify_free(quvi_verify_t);

  void quvi_verify_get(quvi_verify_t, QuviVerifyProperty, ...);

  /* Convenience */

  QuviBoolean quvi_supports(quvi_t, const char*,
                            QuviSupportsMode, QuviSupportsType);

  const char *quvi_version(QuviVersion);

  const char *quvi_errmsg(quvi_t);
  QuviBoolean quvi_ok(quvi_t);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* qfunc_h */

/* vim: set ts=2 sw=2 tw=72 expandtab: */
