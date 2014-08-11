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
	egl \
	gbm \
	drm \
	llvm

lua:
	test -d lua || mkdir lua
	test -f $@/luacxx.so || ln -s ../src/.libs/libluacxx.so $@/luacxx.so
	test -d $@/acme || ln -s ../$(top_srcdir)/src/acme $@/acme
	test -f $@/luacxx || ln -s ../src/luacxx $@/luacxx
	test -f $@/demo.lua || ln -s ../$(top_srcdir)/src/demo.lua $@/demo.lua
	for lib in $(luacxx_libraries); do \
		test -f $@/$$lib.so || ln -s ../src/.libs/libluacxx-$$lib.so $@/$$lib.so; \
	done;
.PHONY: lua

LUA_LIB_DIR="$(libdir)/lua/5.2/"

install-exec-hook:
	mkdir -p $(DESTDIR)$(LUA_LIB_DIR)
	test -f $(DESTDIR)$(LUA_LIB_DIR)/libluacxx.so || \
		ln -s $(libdir)/libluacxx.so $(DESTDIR)$(LUA_LIB_DIR);
	for lib in $(luacxx_libraries); do \
		test -f $(DESTDIR)$(LUA_LIB_DIR)/$$lib.so || \
			ln -s $(libdir)/libluacxx-$$lib.so $(DESTDIR)$(LUA_LIB_DIR)/$$lib.so; \
	done;

checkdebug: $(TESTS)
	gdb ./src/.libs/lt-runtest

checkvalgrind:
	valgrind -v --leak-check=full ./src/.libs/lt-runtest

VALGRIND = valgrind -v --num-callers=40 --leak-check=full --trace-children=yes

valgrind:
	cd lua && $(VALGRIND) ./luacxx demo.lua Gst

run: lua
	cd lua && ./luacxx demo.lua Gst

debug: lua
	cd lua && gdb ../src/.libs/lt-luacxx

run-quat_benchmark:
	cd lua && ./luacxx demo.lua quat_benchmark

run-gtk_gstreamer:
	cd lua && ./luacxx demo.lua gtk_gstreamer

run-qt_window:
	cd lua && ./luacxx demo.lua qt_window

run-cairo:
	cd lua && ./luacxx demo.lua cairo

run-Gst:
	cd lua && ./luacxx demo.lua Gst

run-ncurses_getch:
	cd lua && ./luacxx demo.lua ncurses_getch

run-nanorecv:
	cd lua && ./luacxx demo.lua nanorecv ipc:///tmp/pipeline.ipc

run-nanosend:
	cd lua && ./luacxx demo.lua nanosend ipc:///tmp/pipeline.ipc "Hello!"

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
