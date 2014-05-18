check_PROGRAMS = runtest
TESTS = $(check_PROGRAMS)

runtest_CXXFLAGS = $(AM_CXXFLAGS) $(QT_CXXFLAGS) @LUA_INCLUDE@ -I$(top_srcdir)/src \
	@BOOST_CPPFLAGS@ \
	-DBOOST_TEST_DYN_LINK \
	-DLUA_DIR=\"$(srcdir)/lua/\"

runtest_LDADD = ../libluacxx.la $(QT_LIBS) @LUA_LIB@ @BOOST_LDFLAGS@ @BOOST_UNIT_TEST_FRAMEWORK_LIB@

runtest_SOURCES = \
	core.cpp \
	main.cpp

EXTRA_DIST = \
	lua/bin/a.lua \
	lua/bin/b.lua \
	lua/anim.lua \
	lua/simple.lua \
	lua/testlib/Library.lua

if BUILD_QT

runtest_MOC_SOURCES = \
	moc_mocks.cpp
nodist_runtest_SOURCES = $(runtest_MOC_SOURCES)

mostlyclean-local:
	rm -f $(runtest_MOC_SOURCES)
.PHONY: mostlyclean-local

moc_%.cpp: %.hpp
	@QT_MOC@ -o $@ $<

endif
