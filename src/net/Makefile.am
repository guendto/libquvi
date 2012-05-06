
src=\
  resolve.c\
  handle.c\
  fetch.c\
  opt.c

hdr=\
  resolve.h\
  handle.h\
  fetch.h\
  opt.h\
  def.h

noinst_LTLIBRARIES=libconvenience_net.la
libconvenience_net_la_SOURCES=$(src) $(hdr)

libconvenience_net_la_CPPFLAGS=\
  -I$(top_srcdir)/src/quvi-1.0/\
  -I$(top_srcdir)/src/\
  $(liblua_CFLAGS)\
  $(glib_CFLAGS)\
  $(AM_CPPFLAGS)

libconvenience_net_la_CFLAGS=$(AM_CFLAGS)

libconvenience_net_la_LDFLAGS=\
  $(liblua_LIBS)\
  $(glib_LIBS)\
  $(AM_LDFLAGS)
