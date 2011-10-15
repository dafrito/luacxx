TEMPLATE = lib
TARGET = 
DEPENDPATH += . lib
INCLUDEPATH += . lib
OBJECTS_DIR = build
MOC_DIR = build

QMAKE_CXXFLAGS += -std=c++0x

# Input
HEADERS += \
	lib/exceptions.hpp \
	lib/loaders.hpp \
	lib/Lua.hpp \
	lib/LuaStack.hpp \
	lib/LuaValue.hpp \
	lib/types.hpp

SOURCES += \
	lib/loaders.cpp \
	lib/Lua.cpp \
	lib/LuaStack.cpp \
	lib/types.cpp
