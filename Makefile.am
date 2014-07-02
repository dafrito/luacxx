ACLOCAL_AMFLAGS = -I m4
SUBDIRS = src

lua:
	test -d lua || mkdir lua
	test -f $@/luacxx.so || ln -s ../src/.libs/libluacxx.so $@/luacxx.so
	test -f $@/ncurses.so || ln -s ../src/.libs/libluacxx-ncurses.so $@/ncurses.so
	test -f $@/Qt5Core.so || ln -s ../src/.libs/libluacxx-Qt5Core.so $@/Qt5Core.so
	test -f $@/Qt5Gui.so || ln -s ../src/.libs/libluacxx-Qt5Gui.so $@/Qt5Gui.so
	test -f $@/nanomsg.so || ln -s ../src/.libs/libluacxx-nanomsg.so $@/nanomsg.so
	test -f $@/libinput.so || ln -s ../src/.libs/libluacxx-libinput.so $@/libinput.so
	test -f $@/libevdev.so || ln -s ../src/.libs/libluacxx-libevdev.so $@/libevdev.so
	test -f $@/linux.so || ln -s ../src/.libs/libluacxx-linux.so $@/linux.so
	cd lua && lua
.PHONY: lua

checkdebug: $(TESTS)
	cd tests && gdb ./src/.libs/lt-runtest

checkvalgrind:
	cd tests && valgrind -v --leak-check=full ./src/.libs/lt-runtest

valgrind:
	LUA_PATH='$(top_srcdir)/src/?.lua;;' LUA_CPATH='./src/.libs/lib?.so;;' valgrind -v --num-callers=40 --leak-check=full --trace-children=yes ./.libs/lt-luacxx $(top_srcdir)/src/demo.lua

run:
	LUA_PATH='$(top_srcdir)/src/?.lua;;' LUA_CPATH='./src/.libs/lib?.so;;' ./src/luacxx $(top_srcdir)/src/demo.lua

debug:
	LUA_PATH='$(top_srcdir)/src/?.lua;;' LUA_CPATH='./src/.libs/lib?.so;;' gdb ./src/.libs/lt-luacxx

run-nanorecv:
	LUA_PATH='$(top_srcdir)/?.lua;;' LUA_CPATH='./.libs/lib?.so;;' ./luacxx $(top_srcdir)/src/demo.lua recv ipc:///tmp/pipeline.ipc

run-nanosend:
	LUA_PATH='$(top_srcdir)/?.lua;;' LUA_CPATH='./.libs/lib?.so;;' ./luacxx $(top_srcdir)/src/demo.lua send ipc:///tmp/pipeline.ipc "Hello!"

RPMFLAGS ?= --ba
SRCRPM=luacxx-@PACKAGE_VERSION@-@PACKAGE_RELEASE@.src.rpm
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
	ln -s $(RPMDIR)/SRPMS/luacxx-@PACKAGE_VERSION@-@PACKAGE_RELEASE@`rpmbuild -E '%{?dist}' rpm.spec`.src.rpm $(SRCRPM)
.PHONY: rpm

$(RPMDIR):
	mkdir -p $@
	cd $@ && mkdir -p SOURCES SPECS BUILD RPMS SRPMS

mostlyclean-local:
	rm -f $(runtest_MOC_SOURCES)
.PHONY: mostlyclean-local

# This is a common typo for me
cehck: check
.PHONY: cehck
