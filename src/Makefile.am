SUBDIRS=quvi-0.9 api misc lua curl net

hdr=\
  _quvi_net_resolve_s.h\
  _quvi_playlist_s.h\
  _quvi_net_opt_s.h\
  _quvi_script_s.h\
  _quvi_verify_s.h\
  _quvi_media_s.h\
  _quvi_scan_s.h\
  _quvi_net_s.h\
  _quvi_macro.h\
  _quvi_s.h

lib_LTLIBRARIES=libquvi-0.9.la
libquvi_0_9_la_SOURCES=$(hdr)

libquvi_0_9_la_CPPFLAGS=\
  -DLOCALEDIR=\""$(localedir)"\"\
  -I$(top_srcdir)/src/quvi-0.9/\
  -I$(top_srcdir)/src/\
  $(libcurl_CFLAGS)\
  $(liblua_CFLAGS)\
  $(glib_CFLAGS)\
  $(AM_CPPFLAGS)

libquvi_0_9_la_CFLAGS=$(AM_CFLAGS)

libquvi_0_9_la_LDFLAGS=\
  -version-info $(LT_CUR):$(LT_REV):$(LT_AGE)\
  $(AM_LDFLAGS)

libquvi_0_9_la_LIBADD=\
  $(top_builddir)/src/misc/libconvenience_misc.la\
  $(top_builddir)/src/curl/libconvenience_curl.la\
  $(top_builddir)/src/net/libconvenience_net.la\
  $(top_builddir)/src/lua/libconvenience_lua.la\
  $(top_builddir)/src/api/libconvenience_api.la\
  $(libcurl_LIBS)\
  $(liblua_LIBS)\
  $(glib_LIBS)\
  $(LTLIBINTL)

# vim: set ts=2 sw=2 tw=72 expandtab:
