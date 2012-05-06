
src=\
  free.c\
  new.c\
  ok.c\
  resolve_destination_url.c\
  resolve_forwarded.c\
  resolve_free.c\
  resolve_new.c

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
  $(liblua_LIBS)\
  $(glib_LIBS)\
  $(AM_LDFLAGS)
