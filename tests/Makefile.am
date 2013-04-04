check_PROGRAMS = runtest newtest
TESTS = $(check_PROGRAMS)

newtest_CXXFLAGS = $(AM_CXXFLAGS) @QT_CXXFLAGS@ -I$(top_srcdir)/include -I$(top_srcdir)/src -DBOOST_TEST_DYN_LINK

# Don't try changing "../src" to use "top_srcdir" - this is referring to the
# built artifact, not something in the source directory
newtest_LDADD = ../src/liblua-cxx.la @QT_LIBS@ @BOOST_UNIT_TEST_FRAMEWORK_LIB@

noinst_HEADERS = \
	init.hpp

newtest_SOURCES = \
	basic.cpp \
	main.cpp

runtest_CXXFLAGS = $(AM_CXXFLAGS) @QT_CXXFLAGS@ -I$(top_srcdir)/include -DLUA_DIR=\"$(srcdir)/lua/\"

# Don't try changing "../src" to use "top_srcdir" - this is referring to the
# built artifact, not something in the source directory
runtest_LDADD = ../src/liblua-cxx.la @QT_LIBS@

test_suites =         \
	LuaStackTests     \
	LuaTests          \
	LoaderTests       \
	LuaTableTests     \
	LuaReferenceTests \
	UserdataTests

runtest_SOURCES =         \
	tests.cpp             \
	mocks.hpp             \
	LuaTests.hpp          \
	LuaStackTests.hpp     \
	LoaderTests.hpp       \
	LuaTableTests.hpp     \
	LuaReferenceTests.hpp \
	UserdataTests.hpp

runtest_MOC_SOURCES = \
	moc_mocks.cpp             \
	moc_LuaTests.cpp          \
	moc_LuaStackTests.cpp     \
	moc_LoaderTests.cpp       \
	moc_LuaTableTests.cpp     \
	moc_LuaReferenceTests.cpp \
	moc_UserdataTests.cpp

nodist_runtest_SOURCES =      \
	$(runtest_MOC_SOURCES)

check_SCRIPTS = \
	lua/bin/a.lua \
	lua/bin/b.lua \
	lua/anim.lua \
	lua/simple.lua \
	lua/testlib/Library.lua

CLEANFILES = tests.cpp $(check_SCRIPTS)

mostlyclean-local:
	rm -f $(runtest_MOC_SOURCES)
.PHONY: mostlyclean-local

tests.cpp: $(top_srcdir)/tests/make_wrapper.sh $(addsuffix .hpp, $(test_suites))
	rm -f $@
	$(top_srcdir)/tests/make_wrapper.sh $^ >$@-wip
	mv $@-wip $@
	chmod -w $@

moc_%.cpp: %.hpp
	@QT_MOC@ -o $@ $<

