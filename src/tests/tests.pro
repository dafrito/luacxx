TEMPLATE = app

CONFIG += qt qtestlib

TARGET = run-tests
INCLUDEPATH += ..
VPATH += ..
OBJECTS_DIR = build
MOC_DIR = build
DESTDIR = ../..

LIBS += -llua

QMAKE_CXXFLAGS += -std=c++0x

HEADERS += \
	loaders.hpp \
	BasicTests.hpp

SOURCES += \
	tests.cpp \
	LuaStack.cpp \
	Lua.cpp \
	types.cpp \
	loaders.cpp
