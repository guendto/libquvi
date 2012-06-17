if WITH_EXAMPLES
noinst_PROGRAMS=\
  query_formats\
  supports\
  playlist\
  version\
  resolve\
  script\
  media\
  scan

CPF=-I$(top_srcdir)/src/quvi-1.0/ $(glib_CFLAGS) $(AM_CPPFLAGS)
LDF= $(AM_LDFLAGS)
LDA=$(top_builddir)/src/libquvi-1.0.la
CMC=exit_if_error.c cleanup.c status.c var.c enable_verbose.c

query_formats_SOURCES=query_formats.c $(CMC)
query_formats_CPPFLAGS=$(CPF)
query_formats_CFLAGS=$(AM_CFLAGS)
query_formats_LDFLAGS=$(LDF)
query_formats_LDADD=$(LDA)

supports_SOURCES=supports.c $(CMC)
supports_CPPFLAGS=$(CPF)
supports_CFLAGS=$(AM_CFLAGS)
supports_LDFLAGS=$(LDF)
supports_LDADD=$(LDA)

playlist_SOURCES=playlist.c $(CMC)
playlist_CPPFLAGS=$(CPF)
playlist_CFLAGS=$(AM_CFLAGS)
playlist_LDFLAGS=$(LDF)
playlist_LDADD=$(LDA)

version_SOURCES=version.c
version_CPPFLAGS=$(CPF)
version_CFLAGS=$(AM_CFLAGS)
version_LDFLAGS=$(LDF)
version_LDADD=$(LDA)

resolve_SOURCES=resolve.c $(CMC)
resolve_CPPFLAGS=$(CPF)
resolve_CFLAGS=$(AM_CFLAGS)
resolve_LDFLAGS=$(LDF)
resolve_LDADD=$(LDA)

script_SOURCES=script.c $(CMC)
script_CPPFLAGS=$(CPF)
script_CFLAGS=$(AM_CFLAGS)
script_LDFLAGS=$(LDF)
script_LDADD=$(LDA)

media_SOURCES=media.c $(CMC)
media_CPPFLAGS=$(CPF)
media_CFLAGS=$(AM_CFLAGS)
media_LDFLAGS=$(LDF)
media_LDADD=$(LDA)

scan_SOURCES=scan.c $(CMC)
scan_CPPFLAGS=$(CPF)
scan_CFLAGS=$(AM_CFLAGS)
scan_LDFLAGS=$(LDF)
scan_LDADD=$(LDA)
endif # WITH_EXAMPLES
