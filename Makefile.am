ACLOCAL_AMFLAGS = -I m4
SUBDIRS = src

lua:
	LUA_CPATH='./src/.libs/lib?.so;;' lua

checkdebug: $(TESTS)
	cd tests && gdb ./src/.libs/lt-runtest

checkvalgrind:
	cd tests && valgrind -v --leak-check=full ./src/.libs/lt-runtest

valgrind:
	LUA_PATH='$(top_srcdir)/src/?.lua;;' LUA_CPATH='./src/.libs/lib?.so;;' valgrind -v --num-callers=40 --leak-check=full --trace-children=yes ./.libs/lt-luacxx $(top_srcdir)/demo.lua

run:
	LUA_PATH='$(top_srcdir)/src/?.lua;;' LUA_CPATH='./src/.libs/lib?.so;;' ./src/luacxx $(top_srcdir)/demo.lua

debug:
	LUA_PATH='$(top_srcdir)/src/?.lua;;' LUA_CPATH='./src/.libs/lib?.so;;' gdb ./src/.libs/lt-luacxx

# This is a common typo for me
cehck: check
.PHONY: cehck

pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = src/rainback.pc

run-nanorecv:
	LUA_PATH='$(top_srcdir)/?.lua;;' LUA_CPATH='./.libs/lib?.so;;' ./luacxx $(top_srcdir)/demo.lua recv ipc:///tmp/pipeline.ipc

run-nanosend:
	LUA_PATH='$(top_srcdir)/?.lua;;' LUA_CPATH='./.libs/lib?.so;;' ./luacxx $(top_srcdir)/demo.lua send ipc:///tmp/pipeline.ipc "Hello!"

RPMFLAGS ?= --ba
SRCRPM=rainback-@PACKAGE_VERSION@-@PACKAGE_RELEASE@.src.rpm
export RPMDIR ?= $$HOME/rpmbuild

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
	ln -s $(RPMDIR)/SRPMS/rainback-@PACKAGE_VERSION@-@PACKAGE_RELEASE@`rpmbuild -E '%{?dist}' rpm.spec`.src.rpm $(SRCRPM)
.PHONY: rpm

$(RPMDIR):
	mkdir -p $@
	cd $@ && mkdir -p SOURCES SPECS BUILD RPMS SRPMS

mostlyclean-local:
	rm -f $(runtest_MOC_SOURCES)
.PHONY: mostlyclean-local

