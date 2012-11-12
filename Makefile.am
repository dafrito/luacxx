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
rpm: rpm.spec dist-gzip | $(RPMDIR)
	cp -u $(PACKAGE_NAME)-$(PACKAGE_VERSION).tar.gz $(RPMDIR)/SOURCES
	cp -u rpm.spec $(RPMDIR)/SPECS/$(PACKAGE_NAME).spec
	rpmbuild $(RPMFLAGS) $(RPMDIR)/SPECS/$(PACKAGE_NAME).spec
	for package in `rpm -q --specfile ./rpm.spec`; do \
		arch=`echo $$package | grep -E -o '[^.]+$$'`; \
		filename="$(RPMDIR)/RPMS/$$arch/$$package.rpm"; \
		[ -e `basename $$filename` ] || ln -s $$filename; \
done
.PHONY: rpm

$(RPMDIR):
	mkdir -p $@
	cd $@ && mkdir -p SOURCES SPECS BUILD RPMS SRPMS
