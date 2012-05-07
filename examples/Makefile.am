if WITH_EXAMPLES
noinst_PROGRAMS=media supports scripts

media_SOURCES=media.c exit_if_error.c cleanup.c
media_CPPFLAGS=-I$(top_srcdir)/src/quvi-1.0/ $(glib_CFLAGS) $(AM_CPPFLAGS)
media_CFLAGS=$(AM_CFLAGS)
media_LDFLAGS=$(top_builddir)/src/libquvi-1.0.la $(glib_LIBS) $(AM_LDFLAGS)

supports_SOURCES=supports.c exit_if_error.c cleanup.c
supports_CPPFLAGS=-I$(top_srcdir)/src/quvi-1.0/ $(glib_CFLAGS) $(AM_CPPFLAGS)
supports_CFLAGS=$(AM_CFLAGS)
supports_LDFLAGS=$(top_builddir)/src/libquvi-1.0.la $(glib_LIBS) $(AM_LDFLAGS)

scripts_SOURCES=scripts.c exit_if_error.c cleanup.c
scripts_CPPFLAGS=-I$(top_srcdir)/src/quvi-1.0/ $(glib_CFLAGS) $(AM_CPPFLAGS)
scripts_CFLAGS=$(AM_CFLAGS)
scripts_LDFLAGS=$(top_builddir)/src/libquvi-1.0.la $(glib_LIBS) $(AM_LDFLAGS)
endif # WITH_EXAMPLES
