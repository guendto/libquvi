
EXTRA_DIST=\
  doxy/chk_support.dp\
  doxy/env.dp\
  doxy/getting_started.dp\
  doxy/glossary.dp\
  doxy/glossary_scripts.dp\
  doxy/glossary_termino.dp\
  doxy/groups.dp\
  doxy/main.dp\
  doxy/parse_media.dp\
  doxy/parse_playlist.dp\
  doxy/query_formats.dp\
  doxy/scan_media.dp\
  doxy/scripts.dp

src=\
  query_formats_next_format.c\
  query_formats_free.c\
  query_formats_new.c\
  playlist_next_media_url.c\
  playlist_free.c\
  playlist_new.c\
  playlist_get.c\
  resolve_destination_url.c\
  resolve_forwarded.c\
  resolve_free.c\
  resolve_new.c\
  script_next.c\
  script_get.c\
  media_free.c\
  media_new.c\
  media_get.c\
  scan_next_media_url.c\
  scan_free.c\
  scan_new.c\
  supports.c\
  version.c\
  errmsg.c\
  free.c\
  new.c\
  set.c\
  get.c\
  ok.c

noinst_LTLIBRARIES=libconvenience_api.la
libconvenience_api_la_SOURCES=$(src)

libconvenience_api_la_CPPFLAGS=\
  -I$(top_srcdir)/src/quvi-1.0/\
  -I$(top_srcdir)/src/\
  $(liblua_CFLAGS)\
  $(glib_CFLAGS)\
  $(AM_CPPFLAGS)

libconvenience_api_la_CFLAGS=$(AM_CFLAGS)

libconvenience_api_la_LDFLAGS=\
  $(AM_LDFLAGS)

libconvenience_api_la_LIBADD=\
  $(liblua_LIBS)\
  $(glib_LIBS)
