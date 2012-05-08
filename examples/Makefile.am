if WITH_EXAMPLES
noinst_PROGRAMS=media supports scripts query_formats playlist version scan

CPF=-I$(top_srcdir)/src/quvi-1.0/ $(glib_CFLAGS) $(AM_CPPFLAGS)
LDF=$(top_builddir)/src/libquvi-1.0.la $(AM_LDFLAGS)

media_SOURCES=media.c exit_if_error.c cleanup.c status.c var.c
media_CPPFLAGS=$(CPF)
media_CFLAGS=$(AM_CFLAGS)
media_LDFLAGS=$(LDF)

supports_SOURCES=supports.c exit_if_error.c cleanup.c status.c var.c
supports_CPPFLAGS=$(CPF)
supports_CFLAGS=$(AM_CFLAGS)
supports_LDFLAGS=$(LDF)

scripts_SOURCES=scripts.c exit_if_error.c cleanup.c var.c
scripts_CPPFLAGS=$(CPF)
scripts_CFLAGS=$(AM_CFLAGS)
scripts_LDFLAGS=$(LDF)

query_formats_SOURCES=query_formats.c exit_if_error.c cleanup.c status.c var.c
query_formats_CPPFLAGS=$(CPF)
query_formats_CFLAGS=$(AM_CFLAGS)
query_formats_LDFLAGS=$(LDF)

playlist_SOURCES=playlist.c exit_if_error.c cleanup.c status.c var.c
playlist_CPPFLAGS=$(CPF)
playlist_CFLAGS=$(AM_CFLAGS)
playlist_LDFLAGS=$(LDF)

scan_SOURCES=scan.c exit_if_error.c cleanup.c status.c var.c
scan_CPPFLAGS=$(CPF)
scan_CFLAGS=$(AM_CFLAGS)
scan_LDFLAGS=$(LDF)

version_SOURCES=version.c
version_CPPFLAGS=$(CPF)
version_CFLAGS=$(AM_CFLAGS)
version_LDFLAGS=$(LDF)
endif # WITH_EXAMPLES
