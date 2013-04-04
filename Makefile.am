ACLOCAL_AMFLAGS = -I m4
SUBDIRS = src tests

pkgdata_DATA = \
	lua-cxx.m4

export RPMDIR ?= $$HOME/rpmbuild

checkdebug: $(TESTS)
	cd tests && gdb .libs/lt-runtest

checkvalgrind:
	cd tests && valgrind -v --leak-check=full .libs/lt-runtest

debug: $(TESTS)
	cd src && gdb lua-cxx

valgrind:
	cd src && valgrind -v --leak-check=full --trace-children=yes lua-cxx

# This is a common typo for me
cehck: check
.PHONY: cehck

RPMFLAGS ?= --ba
SRCRPM=lua-cxx-@PACKAGE_VERSION@-@PACKAGE_RELEASE@.src.rpm

rpm: $(SRCRPM)
$(SRCRPM): rpm.spec $(DISTFILES)
	$(MAKE) dist-gzip $(RPMDIR)
	cp -u $(PACKAGE_NAME)-$(PACKAGE_VERSION).tar.gz $(RPMDIR)/SOURCES
	cp -u rpm.spec $(RPMDIR)/SPECS/$(PACKAGE_NAME).spec
	rpmbuild $(RPMFLAGS) $(RPMDIR)/SPECS/$(PACKAGE_NAME).spec
	for package in `rpm -q --specfile rpm.spec`; do \
		arch=`echo $$package | grep -E -o '[^.]+$$'`; \
		filename="$(RPMDIR)/RPMS/$$arch/$$package.rpm"; \
		[ -e `basename $$filename` ] || ln -s $$filename; \
	done
	rm -f $@
	ln -s $(RPMDIR)/SRPMS/lua-cxx-@PACKAGE_VERSION@-@PACKAGE_RELEASE@`rpmbuild -E '%{?dist}' rpm.spec`.src.rpm $@
.PHONY: rpm

$(RPMDIR):
	mkdir -p $@
	cd $@ && mkdir -p SOURCES SPECS BUILD RPMS SRPMS
