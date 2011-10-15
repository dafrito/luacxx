TEMPLATE = lib
TARGET = 
DEPENDPATH += . src
INCLUDEPATH += . src
OBJECTS_DIR = build
MOC_DIR = build

QMAKE_CXXFLAGS += -std=c++0x

# Input
HEADERS += \
	src/exceptions.hpp \
	src/loaders.hpp \
	src/Lua.hpp \
	src/LuaStack.hpp \
	src/LuaValue.hpp \
	src/types.hpp

SOURCES += \
	src/loaders.cpp \
	src/Lua.cpp \
	src/LuaStack.cpp \
	src/types.cpp \
