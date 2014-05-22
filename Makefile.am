ACLOCAL_AMFLAGS = -I m4
SUBDIRS = src src/tests

pkgdata_DATA = \
	luacxx.m4

pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = luacxx.pc

export RPMDIR ?= $$HOME/rpmbuild

checkdebug: $(TESTS)
	cd src/tests && gdb .libs/lt-runtest

checkvalgrind:
	cd src/tests && valgrind -v --leak-check=full .libs/lt-runtest

debug: $(TESTS)
	cd src && gdb luacxx

valgrind:
	cd src && valgrind -v --leak-check=full --trace-children=yes luacxx

lua:
	LUA_CPATH='./src/.libs/lib?.so;;' lua

# This is a common typo for me
cehck: check
.PHONY: cehck

RPMFLAGS ?= --ba
SRCRPM=luacxx-@PACKAGE_VERSION@-@PACKAGE_RELEASE@.src.rpm

rpm:
	$(MAKE) dist-gzip $(RPMDIR)
	cp -u $(PACKAGE_NAME)-$(PACKAGE_VERSION).tar.gz $(RPMDIR)/SOURCES
	cp -u rpm.spec $(RPMDIR)/SPECS/$(PACKAGE_NAME).spec
	rpmbuild $(RPMFLAGS) $(RPMDIR)/SPECS/$(PACKAGE_NAME).spec
	for package in `rpm -q --specfile rpm.spec`; do \
		arch=`echo $$package | grep -E -o '[^.]+$$'`; \
		filename="$(RPMDIR)/RPMS/$$arch/$$package.rpm"; \
		[ -e `basename $$filename` ] || ln -s $$filename; \
	done
	rm -f $(SRCRPM)
	ln -s $(RPMDIR)/SRPMS/luacxx-@PACKAGE_VERSION@-@PACKAGE_RELEASE@`rpmbuild -E '%{?dist}' rpm.spec`.src.rpm $(SRCRPM)
.PHONY: rpm

$(RPMDIR):
	mkdir -p $@
	cd $@ && mkdir -p SOURCES SPECS BUILD RPMS SRPMS
