if WITH_EXAMPLES
noinst_PROGRAMS=media

media_SOURCES=media.c exit_if_error.c cleanup.c
media_CPPFLAGS=-I$(top_srcdir)/src/quvi-1.0/ $(glib_CFLAGS) $(AM_CPPFLAGS)
media_CFLAGS=$(AM_CFLAGS)
media_LDFLAGS=$(top_builddir)/src/libquvi-1.0.la $(glib_LIBS) $(AM_LDFLAGS)
endif # WITH_EXAMPLES
