libquvisubincludedir=$(includedir)/quvi-0.9/quvi
libquvisubinclude_HEADERS=\
  qplaylistprop.h\
  qhttpmiprop.h\
  qmediaprop.h\
  qsubtprop.h\
  qcallback.h\
  qversion.h\
  qoption.h\
  qscript.h\
  qerror.h\
  qsupp.h\
  qbool.h\
  qinfo.h\
  qfunc.h\
  qdef.h

install-data-local:
	@if test -f $(libquvisubincludedir)/qfunc.h ; then \
		echo "** Old headers found in $(libquvisubincludedir).  You should" ; \
		echo "** remove the contents of this directory and type 'make " ; \
		echo "** install' again." ; \
		false ; \
	fi
