
src=\
  scan_scripts.c\
  script_free.c\
  capture.c\
  resolve.c\
  to_utf8.c\
  match.c\
  sort.c\
  trim.c

hdr=\
  script_free.h\
  resolve.h\
  sort.h\
  re.h

noinst_LTLIBRARIES=libconvenience_misc.la
libconvenience_misc_la_SOURCES=$(src) $(hdr)

libconvenience_misc_la_CPPFLAGS=\
  -I$(top_srcdir)/src/quvi-1.0/\
  -I$(top_srcdir)/src/\
  $(glib_CFLAGS)\
  $(AM_CPPFLAGS)

libconvenience_misc_la_CFLAGS=$(AM_CFLAGS)

libconvenience_misc_la_LDFLAGS=\
  $(glib_LIBS)\
  $(AM_LDFLAGS)
