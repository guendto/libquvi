MAN7_TXT=quvi-object.7.txt
DOC_MAN7=quvi-object.7

MAN_TXT=$(MAN7_TXT)

if HAVE_A2X
$(DOC_MAN7):
	$(AM_V_GEN)$(A2X) -f manpage -D $(builddir) $(srcdir)/$@.txt
doc: $(DOC_MAN7)
else
doc:
	@echo configure did not find a2x
endif # HAVE_A2X

MOSTLYCLEANFILES=$(DOC_MAN7)
dist_man_MANS=$(DOC_MAN7)
EXTRA_DIST=$(MAN_TXT)

# vim: set ts=2 sw=2 tw=72 expandtab:
