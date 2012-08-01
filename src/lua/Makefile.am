
src=\
  util/exec_util_resolve_redirections.c\
  util/exec_util_convert_entities.c\
  util/exec_util_to_file_ext.c\
  chk_accepts.c\
  exec_playlist_script_ident.c\
  exec_playlist_script_parse.c\
  exec_media_script_ident.c\
  exec_media_script_parse.c\
  exec_scan_script_parse.c\
  match_url_to_playlist_script.c\
  match_url_to_media_script.c\
  load_util_script.c\
  modify_pkgpath.c\
  getfield.c\
  setfield.c\
  init.c\
  quvi/resolve.c\
  quvi/fetch.c

hdr=\
  chk_accepts.h\
  load_util_script.h\
  getfield.h\
  setfield.h\
  exec.h\
  def.h

noinst_LTLIBRARIES=libconvenience_lua.la
libconvenience_lua_la_SOURCES=$(src) $(hdr)

libconvenience_lua_la_CPPFLAGS=\
  -I$(top_srcdir)/src/quvi-1.0/\
  -I$(top_srcdir)/src/\
  $(liblua_CFLAGS)\
  $(glib_CFLAGS)\
  $(AM_CPPFLAGS)

libconvenience_lua_la_CFLAGS=$(AM_CFLAGS)

libconvenience_lua_la_LDFLAGS=\
  $(AM_LDFLAGS)

libconvenience_lua_la_LIBADD=\
  $(liblua_LIBS)\
  $(glib_LIBS)
