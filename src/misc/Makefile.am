
src=\
  match_playlist_script.c\
  match_media_script.c\
  scan_scripts.c\
  script_free.c\
  scan_new.c\
  playlist.c\
  capture.c\
  resolve.c\
  to_utf8.c\
  media.c\
  match.c\
  trim.c

hdr=\
  match_playlist_script.h\
  match_media_script.h\
  script_free.h\
  scan_new.h\
  playlist.h\
  resolve.h\
  media.h\
  re.h

noinst_LTLIBRARIES=libconvenience_misc.la
libconvenience_misc_la_SOURCES=$(src) $(hdr)

libconvenience_misc_la_CPPFLAGS=\
  -I$(top_srcdir)/src/quvi-0.9/\
  -I$(top_srcdir)/src/\
  $(glib_CFLAGS)\
  $(AM_CPPFLAGS)

libconvenience_misc_la_CFLAGS=$(AM_CFLAGS)

libconvenience_misc_la_LDFLAGS=\
  $(AM_LDFLAGS)

libconvenience_misc_la_LIBADD=\
  $(glib_LIBS)
