ACLOCAL_AMFLAGS = -I m4
SUBDIRS = src

pkgdata_DATA = \
	rainback.m4

pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = rainback.pc

export RPMDIR ?= $$HOME/rpmbuild

checkdebug: $(TESTS)
	cd src/tests && gdb .libs/lt-runtest

checkvalgrind:
	cd src/tests && valgrind -v --leak-check=full .libs/lt-runtest

valgrind:
	LUA_PATH='$(top_srcdir)/src/?.lua;;' LUA_CPATH='./src/.libs/lib?.so;;' valgrind -v --num-callers=40 --leak-check=full --trace-children=yes ./src/.libs/lt-luacxx $(top_srcdir)/src/demo.lua

lua:
	LUA_CPATH='./src/.libs/lib?.so;;' lua

run:
	LUA_PATH='$(top_srcdir)/src/?.lua;;' LUA_CPATH='./src/.libs/lib?.so;;' ./src/luacxx $(top_srcdir)/src/demo.lua

run-nanorecv:
	LUA_PATH='$(top_srcdir)/src/?.lua;;' LUA_CPATH='./src/.libs/lib?.so;;' ./src/luacxx $(top_srcdir)/src/demo.lua recv ipc:///tmp/pipeline.ipc

run-nanosend:
	LUA_PATH='$(top_srcdir)/src/?.lua;;' LUA_CPATH='./src/.libs/lib?.so;;' ./src/luacxx $(top_srcdir)/src/demo.lua send ipc:///tmp/pipeline.ipc "Hello!"

debug:
	LUA_PATH='$(top_srcdir)/src/?.lua;;' LUA_CPATH='./src/.libs/lib?.so;;' gdb ./src/.libs/lt-luacxx

# This is a common typo for me
cehck: check
.PHONY: cehck

RPMFLAGS ?= --ba
SRCRPM=rainback-@PACKAGE_VERSION@-@PACKAGE_RELEASE@.src.rpm

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
