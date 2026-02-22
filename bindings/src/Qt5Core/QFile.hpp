#ifndef luacxx_QFile_INCLUDED
#define luacxx_QFile_INCLUDED

#include "Qt5Core.hpp"
#include "QFileDevice.hpp"

#include <QFile>

LUA_METATABLE_INHERIT(QFile, QFileDevice)

extern "C" int luaopen_Qt5Core_QFile(lua_State* const);

#endif // luacxx_QFile_INCLUDED
