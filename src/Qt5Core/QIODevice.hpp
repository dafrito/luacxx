#ifndef LUACXX_QIODevice_INCLUDED
#define LUACXX_QIODevice_INCLUDED

#include "Qt5Core.hpp"
#include "../enum.hpp"

#include <QIODevice>

LUA_METATABLE_BUILT(QIODevice)
LUA_METATABLE_ENUM(QIODevice::OpenModeFlag);

extern "C" int luaopen_Qt5Core_QIODevice(lua_State* const);

#endif // LUACXX_QIODevice_INCLUDED

