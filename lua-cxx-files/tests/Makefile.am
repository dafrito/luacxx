LUA_INCLUDE = @LUA_INCLUDE@
LUA_LIB = @LUA_LIB@

QT_CXXFLAGS = @QT_CXXFLAGS@
QT_LIBS = @QT_LIBS@
QT_MOC = @QT_MOC@

check_PROGRAMS = runtest
runtest_CXXFLAGS = $(AM_CXXFLAGS) $(QT_CXXFLAGS) $(LUA_INCLUDE)
runtest_LDADD = $(QT_LIBS) $(LUA_LIB) ../lib/libluacxx.la

TESTS = $(check_PROGRAMS)

test_suites =         \
	LuaTests          \
	LuaStackTests     \
	LoaderTests       \
	LuaReferenceTests

runtest_SOURCES =         \
	tests.cpp             \
	mocks.hpp             \
	LuaTests.hpp          \
	LuaStackTests.hpp     \
	LoaderTests.hpp       \
	LuaReferenceTests.hpp

nodist_runtest_SOURCES =      \
	moc_mocks.cpp             \
	moc_LuaTests.cpp          \
	moc_LuaStackTests.cpp     \
	moc_LoaderTests.cpp       \
	moc_LuaReferenceTests.cpp

check_SCRIPTS = \
	anim.lua \
	simple.lua

CLEANFILES = $(check_SCRIPTS)

tests.cpp: $(addsuffix .hpp, $(test_suites))
	rm -f $@
	./make_wrapper.sh $^ >$@-wip
	mv $@-wip $@
	chmod -w $@

anim.lua:
	echo "function Tick(square, elapsed)" >>$@
	echo "	square.x = 250 * math.cos(elapsed);" >>$@
	echo "end" >>$@

simple.lua:
	echo "assert(_G['No']=='Time');" >$@

moc_%.cpp: %.hpp
	$(QT_MOC) -o $@ $<
