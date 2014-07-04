ACLOCAL_AMFLAGS = -I m4
SUBDIRS = src

luacxx_libraries = \
	ncurses \
	Qt5Core \
	Qt5Gui \
	nanomsg \
	libinput \
	libevdev \
	linux \

lua:
	test -d lua || mkdir lua
	test -f $@/luacxx.so || ln -s ../src/.libs/libluacxx.so $@/luacxx.so
	test -d $@/demo || ln -s ../$(top_srcdir)/src/demo $@/demo
	test -f $@/luacxx || ln -s ../src/luacxx $@/luacxx
	for lib in $(luacxx_libraries); do \
		test -f $@/$$lib.so || ln -s ../src/.libs/libluacxx-ncurses.so $@/$$lib.so; \
	done;
.PHONY: lua

LUA_LIB_DIR="$(libdir)/lua/5.2/"

install-exec-hook:
	mkdir -p $(DESTDIR)/$(LUA_LIB_DIR)
	ln -s $(libdir)/libluacxx.so $(DESTDIR)/$(LUA_LIB_DIR)
	for lib in $(luacxx_libraries); do \
		ln -s $(libdir)/libluacxx-$$lib.so $(DESTDIR)/$(LUA_LIB_DIR)/$$lib.so
	done;

checkdebug: $(TESTS)
	cd tests && gdb ./src/.libs/lt-runtest

checkvalgrind:
	cd tests && valgrind -v --leak-check=full ./src/.libs/lt-runtest

valgrind:
	LUA_PATH='$(top_srcdir)/src/?.lua;;' LUA_CPATH='./src/.libs/lib?.so;./src/.libs/libluacxx-?.so;;' valgrind -v --num-callers=40 --leak-check=full --trace-children=yes ./src/.libs/lt-luacxx $(top_srcdir)/src/demo/main.lua

run: lua
	cd lua && ./luacxx demo/main.lua

debug: lua
	cd lua && gdb ../src/.libs/lt-luacxx

run-nanorecv:
	cd lua && ./luacxx demo/main.lua recv ipc:///tmp/pipeline.ipc

run-nanosend:
	cd lua && ./luacxx demo/main.lua send ipc:///tmp/pipeline.ipc "Hello!"

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
