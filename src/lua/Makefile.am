
src=\
  quvi/resolve.c\
  quvi/fetch.c\
  modify_pkgpath.c\
  getfield.c\
  init.c

hdr=\
  getfield.h\
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
  $(liblua_LIBS)\
  $(glib_LIBS)\
  $(AM_LDFLAGS)
