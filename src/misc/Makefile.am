
src=\
  match_subtitle_export_script.c\
  match_subtitle_script.c\
  match_playlist_script.c\
  match_media_script.c\
  scan_scripts.c\
  script_free.c\
  scan_new.c\
  subtitle_export.c\
  subtitle.c\
  playlist.c\
  unescape.c\
  capture.c\
  resolve.c\
  to_utf8.c\
  media.c\
  match.c\
  trim.c

hdr=\
  match_subtitle_export_script.h\
  match_subtitle_script.h\
  match_playlist_script.h\
  match_media_script.h\
  subtitle_export.h\
  script_free.h\
  subtitle.h\
  unescape.h\
  scan_new.h\
  playlist.h\
  resolve.h\
  media.h\
  re.h

noinst_LTLIBRARIES=libconvenience_misc.la
libconvenience_misc_la_SOURCES=$(src) $(hdr)

libconvenience_misc_la_CPPFLAGS=\
  -DLOCALEDIR=\""$(localedir)"\"\
  -I$(top_srcdir)/src/quvi-0.9/\
  -I$(top_srcdir)/src/\
  $(glib_CFLAGS)\
  $(AM_CPPFLAGS)

libconvenience_misc_la_CFLAGS=$(AM_CFLAGS)

libconvenience_misc_la_LDFLAGS=\
  $(AM_LDFLAGS)

libconvenience_misc_la_LIBADD=\
  $(glib_LIBS)
