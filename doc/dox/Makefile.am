.PHONY: doc distdoc-html

if HAVE_DOXYGEN
doc:
	@$(DOXYGEN) Doxyfile
distdoc-html: doc
	@tar chof - libquvi-@VERSION@ | \
			XZ_OPT=-6 xz -c >@top_builddir@/libquvi-html-@VERSION@.tar.xz \
			&& echo Created libquvi-html-@VERSION@.tar.xz
else
doc:
distdoc-html: doc
	@echo configure did not find doxygen
endif

clean-local:
	@rm -rf libquvi-@VERSION@
