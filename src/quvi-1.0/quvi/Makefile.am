libquvisubincludedir=$(includedir)/quvi-1.0/quvi
libquvisubinclude_HEADERS=\
  qversion.h\
  qsupp.h\
  qprotocat.h\
  qmediaprop.h\
  qplaylistprop.h\
  qscript.h\
  qcallback.h\
  qbool.h\
  qdef.h\
  qinfo.h\
  qoption.h\
  qerror.h\
  qfunc.h

install-data-local:
	@if test -f $(libquvisubincludedir)/qfunc.h ; then \
		echo "** Old headers found in $(libquvisubincludedir).  You should" ; \
		echo "** remove the contents of this directory and type 'make " ; \
		echo "** install' again." ; \
		false ; \
	fi
