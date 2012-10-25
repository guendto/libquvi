src=\
  http_metainfo.c\
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
  -DLOCALEDIR=\""$(localedir)"\"\
  -I$(top_srcdir)/src/quvi-0.9/\
  -I$(top_srcdir)/src/\
  $(liblua_CFLAGS)\
  $(glib_CFLAGS)\
  $(AM_CPPFLAGS)

libconvenience_net_la_CFLAGS=$(AM_CFLAGS)

libconvenience_net_la_LDFLAGS=\
  $(AM_LDFLAGS)

libconvenience_net_la_LIBADD=\
  $(liblua_LIBS)\
  $(glib_LIBS)
