if WITH_EXAMPLES
noinst_PROGRAMS=media supports scripts query_formats playlist

media_SOURCES=media.c exit_if_error.c cleanup.c
media_CPPFLAGS=-I$(top_srcdir)/src/quvi-1.0/ $(glib_CFLAGS) $(AM_CPPFLAGS)
media_CFLAGS=$(AM_CFLAGS)
media_LDFLAGS=$(top_builddir)/src/libquvi-1.0.la $(AM_LDFLAGS)

supports_SOURCES=supports.c exit_if_error.c cleanup.c
supports_CPPFLAGS=-I$(top_srcdir)/src/quvi-1.0/ $(glib_CFLAGS) $(AM_CPPFLAGS)
supports_CFLAGS=$(AM_CFLAGS)
supports_LDFLAGS=$(top_builddir)/src/libquvi-1.0.la $(AM_LDFLAGS)

scripts_SOURCES=scripts.c exit_if_error.c cleanup.c
scripts_CPPFLAGS=-I$(top_srcdir)/src/quvi-1.0/ $(glib_CFLAGS) $(AM_CPPFLAGS)
scripts_CFLAGS=$(AM_CFLAGS)
scripts_LDFLAGS=$(top_builddir)/src/libquvi-1.0.la $(AM_LDFLAGS)

query_formats_SOURCES=query_formats.c exit_if_error.c cleanup.c
query_formats_CPPFLAGS=-I$(top_srcdir)/src/quvi-1.0/ $(glib_CFLAGS) $(AM_CPPFLAGS)
query_formats_CFLAGS=$(AM_CFLAGS)
query_formats_LDFLAGS=$(top_builddir)/src/libquvi-1.0.la $(AM_LDFLAGS)

playlist_SOURCES=playlist.c exit_if_error.c cleanup.c
playlist_CPPFLAGS=-I$(top_srcdir)/src/quvi-1.0/ $(glib_CFLAGS) $(AM_CPPFLAGS)
playlist_CFLAGS=$(AM_CFLAGS)
playlist_LDFLAGS=$(top_builddir)/src/libquvi-1.0.la $(AM_LDFLAGS)
endif # WITH_EXAMPLES
