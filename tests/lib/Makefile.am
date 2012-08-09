src=env.c qerr.c re.c
hdr=tests.h

noinst_LTLIBRARIES=libconvenience_test.la
libconvenience_test_la_SOURCES=$(src) $(hdr)

libconvenience_test_la_CPPFLAGS=\
  -I$(top_srcdir)/tests/lib/\
  -I$(top_srcdir)/src/quvi-1.0/\
  $(libcurl_CFLAGS)\
  $(glib_CFLAGS)\
  $(AM_CPPFLAGS)

libconvenience_test_la_LDFLAGS=\
  $(AM_LDFLAGS)

libconvenience_test_la_LIBADD=\
  $(libcurl_LIBS)\
  $(glib_LIBS)
