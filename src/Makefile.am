SUBDIRS=quvi-1.0 api misc lua curl net

hdr=\
  _quvi_query_formats_s.h\
  _quvi_net_resolve_s.h\
  _quvi_util_script_s.h\
  _quvi_playlist_s.h\
  _quvi_net_opt_s.h\
  _quvi_script_s.h\
  _quvi_media_s.h\
  _quvi_net_s.h\
  _quvi_macro.h\
  _quvi_s.h

lib_LTLIBRARIES=libquvi-1.0.la
libquvi_1_0_la_SOURCES=$(hdr)

libquvi_1_0_la_CPPFLAGS=\
  -I$(top_srcdir)/src/quvi-1.0/\
  -I$(top_srcdir)/src/\
  $(libcurl_CFLAGS)\
  $(liblua_CFLAGS)\
  $(glib_CFLAGS)\
  $(AM_CPPFLAGS)

libquvi_1_0_la_CFLAGS=$(AM_CFLAGS)

libquvi_1_0_la_LDFLAGS=\
  -version-info $(LT_CUR):$(LT_REV):$(LT_AGE)\
  $(top_builddir)/src/misc/libconvenience_misc.la\
  $(top_builddir)/src/curl/libconvenience_curl.la\
  $(top_builddir)/src/net/libconvenience_net.la\
  $(top_builddir)/src/lua/libconvenience_lua.la\
  $(top_builddir)/src/api/libconvenience_api.la\
  $(libcurl_LIBS)\
  $(liblua_LIBS)\
  $(glib_LIBS)\
  $(AM_LDFLAGS)
