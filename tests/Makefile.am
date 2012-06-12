LUA_INCLUDE = @LUA_INCLUDE@
LUA_LIB = @LUA_LIB@

QT_CXXFLAGS = @QT_CXXFLAGS@
QT_LIBS = @QT_LIBS@
QT_MOC = @QT_MOC@

check_PROGRAMS = runtest
runtest_CXXFLAGS = $(QT_CXXFLAGS) $(LUA_INCLUDE)
runtest_LIBADD = $(QT_LIBS) $(LUA_LIB)

runtest_SOURCES = \
	tests.cpp

nodist_runtest_SOURCES = \
	moc_mocks.cpp \
	moc_BasicTests.cpp \
	moc_TableTests.cpp

runtest_HEADERS = \
	BasicTests.hpp \
	TableTests.hpp \
	mocks.hpp

EXTRA_DIST = \
	anim.lua \
	simple.lua

anim.lua:
	cat >$@ <<EOF \
	function Tick(square, elapsed) \
		square.x = 250 * math.cos(elapsed); \
	end

simple.lua:
	echo "assert(_G['No']=="Time");" >$@

moc_mocks.cpp: mocks.hpp
	$(QT_MOC) -o $@ $<

moc_TableTests.cpp: TableTests.hpp
	$(QT_MOC) -o $@ $<

moc_BasicTests.cpp: BasicTests.hpp
	$(QT_MOC) -o $@ $<
