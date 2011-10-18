TEMPLATE = lib
TARGET = lua-cxx

OBJECTS_DIR = ../build
MOC_DIR = ../build
DESTDIR = ..

exists(/usr/include/lua5.1) {
	# Linux Mint and likely Ubuntu
	INCLUDEPATH  += /usr/include/lua5.1
	LIBS += -llua5.1
}

exists(/usr/include/lua.hpp) {
	# Fedora
	LIBS += -llua
}

QMAKE_CXXFLAGS += -std=c++0x

HEADERS *= exceptions.hpp
HEADERS *= loaders.hpp
HEADERS *= Lua.hpp
HEADERS *= LuaStack.hpp
HEADERS *= LuaValue.hpp
HEADERS *= LuaGlobal.hpp
HEADERS *= LuaReference.hpp
HEADERS *= types.hpp

SOURCES *= loaders.cpp
SOURCES *= Lua.cpp
SOURCES *= LuaStack.cpp
SOURCES *= LuaValue.cpp
SOURCES *= types.cpp
