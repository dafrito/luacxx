QT_MOC = @QT_MOC@
LUA_INCLUDE = @LUA_INCLUDE@
LUA_LIB = @LUA_LIB@

QT_CXXFLAGS = @QT_CXXFLAGS@
QT_LIBS = @QT_LIBS@
QT_MOC = @QT_MOC@

lib_LTLIBRARIES = libluacxx.la
libluacxx_la_CXXFLAGS = $(QT_CXXFLAGS) $(LUA_INCLUDE)
libluacxx_la_LIBADD = $(QT_LIBS) $(LUA_LIB)
libluacxx_la_SOURCES = \
	loaders.hpp \
	Lua.hpp \
	LuaStack.hpp \
	LuaValue.hpp \
	LuaGlobal.hpp \
	LuaReference.hpp \
	types.hpp \
	LuaException.hpp \
	loaders.cpp \
	Lua.cpp \
	LuaStack.cpp \
	LuaValue.cpp \
	types.cpp

nodist_libluacxx_la_SOURCES = \
	moc_Lua.cpp

pkginclude_HEADERS = \
	loaders.hpp \
	Lua.hpp \
	LuaStack.hpp \
	LuaValue.hpp \
	LuaGlobal.hpp \
	LuaReference.hpp \
	types.hpp \
	LuaException.hpp

moc_Lua.cpp: Lua.hpp
	$(QT_MOC) -o $@ $<
