
EXTRA_DIST=\
  doxy/acc_script_prop.dp\
  doxy/chk_support.dp\
  doxy/dirs.dp\
  doxy/env.dp\
  doxy/getting_started.dp\
  doxy/glossary.dp\
  doxy/glossary_scripts.dp\
  doxy/glossary_termino.dp\
  doxy/groups.dp\
  doxy/parse_media.dp\
  doxy/parse_playlist.dp\
  doxy/proxy_support.dp\
  doxy/scan_media.dp\
  doxy/select_stream.dp\
  doxy/verify_url.dp

src=\
  playlist_media_reset.c\
  playlist_media_next.c\
  playlist_free.c\
  playlist_new.c\
  playlist_get.c\
  resolve_destination_url.c\
  resolve_forwarded.c\
  resolve_free.c\
  resolve_new.c\
  script_next.c\
  script_get.c\
  verify_free.c\
  verify_new.c\
  verify_get.c\
  media_stream_choose_best.c\
  media_stream_select.c\
  media_stream_reset.c\
  media_stream_next.c\
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
  -DLOCALEDIR=\""$(localedir)"\"\
  -I$(top_srcdir)/src/quvi-0.9/\
  -I$(top_srcdir)/src/\
  $(libproxy_CFLAGS)\
  $(liblua_CFLAGS)\
  $(glib_CFLAGS)\
  $(AM_CPPFLAGS)

libconvenience_api_la_CFLAGS=$(AM_CFLAGS)

libconvenience_api_la_LDFLAGS=\
  $(AM_LDFLAGS)

libconvenience_api_la_LIBADD=\
  $(libproxy_LIBS)\
  $(liblua_LIBS)\
  $(glib_LIBS)
