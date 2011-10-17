TEMPLATE = lib
TARGET = lua-cxx

OBJECTS_DIR = ../build
MOC_DIR = ../build
DESTDIR = ..

LIBS += -llua
QMAKE_CXXFLAGS += -std=c++0x

HEADERS += \
	exceptions.hpp \
	loaders.hpp \
	Lua.hpp \
	LuaStack.hpp \
	LuaValue.hpp \
	LuaGlobal.hpp \
	types.hpp \

SOURCES += \
	loaders.cpp \
	Lua.cpp \
	LuaStack.cpp \
	types.cpp
