
src=\
  autoproxy.c\
  resolve.c\
  verify.c\
  close.c\
  fetch.c\
  init.c\
  temp.c

hdr=\
  autoproxy.h\
  temp.h

noinst_LTLIBRARIES=libconvenience_curl.la
libconvenience_curl_la_SOURCES=$(src) $(hdr)

libconvenience_curl_la_CPPFLAGS=\
  -I$(top_srcdir)/src/quvi-0.9/\
  -I$(top_srcdir)/src/\
  $(libproxy_CFLAGS)\
  $(libcurl_CFLAGS)\
  $(glib_CFLAGS)\
  $(AM_CPPFLAGS)

libconvenience_curl_la_CFLAGS=$(AM_CFLAGS)

libconvenience_curl_la_LDFLAGS=\
  $(AM_LDFLAGS)

libconvenience_curl_la_LIBADD=\
  $(libproxy_LIBS)\
  $(libcurl_LIBS)\
  $(glib_LIBS)
