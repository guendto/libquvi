ACLOCAL_AMFLAGS=-I m4
EXTRA_DIST=libquvi-0.9.pc.in gen-ver.sh VERSION

pkgconfigdir=	$(libdir)/pkgconfig
pkgconfig_DATA=	libquvi-0.9.pc

SUBDIRS=	src examples doc tests

.PHONY: doc distdoc distdoc-html ChangeLog VERSION test test-mem

check: test

test: all
	@(cd tests ; $(MAKE) test)

test-mem: all
	@(cd tests ; $(MAKE) test-mem)

doc:
	@make -C $(top_builddir)/doc/dox/ doc

distdoc-html:
	@make -C $(top_builddir)/doc/dox/ distdoc-html

distdoc: distdoc-html

VERSION:
	@if test -d "$(top_srcdir)/.git" -o -f "$(top_srcdir)/.git"; then \
		"$(top_srcdir)/gen-ver.sh" "$(top_srcdir)" > $@; \
	fi

ChangeLog:
	@if test -d "$(top_srcdir)/.git" -o -f "$(top_srcdir)/.git"; then \
		git log --stat --name-only --date=short --abbrev-commit > $@; \
	fi

dist-hook: ChangeLog VERSION
