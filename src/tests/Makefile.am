check_PROGRAMS = runtest
TESTS = $(check_PROGRAMS)

runtest_CXXFLAGS = $(AM_CXXFLAGS) @QT_CXXFLAGS@ @LUA_INCLUDE@ -I$(top_srcdir)/src \
	@BOOST_CPPFLAGS@ \
	-DBOOST_TEST_DYN_LINK \
	-DLUA_DIR=\"$(srcdir)/lua/\"

runtest_LDADD = ../liblua-cxx.la @QT_LIBS@ @LUA_LIB@ @BOOST_LDFLAGS@ @BOOST_UNIT_TEST_FRAMEWORK_LIB@

noinst_HEADERS = \
	mocks.hpp \
	init.hpp

runtest_SOURCES = \
	stack.cpp \
	lua.cpp \
	loader.cpp \
	references.cpp \
	table.cpp \
	userdata.cpp \
	insertion.cpp \
	main.cpp

runtest_MOC_SOURCES = \
	moc_mocks.cpp

nodist_runtest_SOURCES = $(runtest_MOC_SOURCES)

EXTRA_DIST = \
	lua/bin/a.lua \
	lua/bin/b.lua \
	lua/anim.lua \
	lua/simple.lua \
	lua/testlib/Library.lua

mostlyclean-local:
	rm -f $(runtest_MOC_SOURCES)
.PHONY: mostlyclean-local

moc_%.cpp: %.hpp
	@QT_MOC@ -o $@ $<

