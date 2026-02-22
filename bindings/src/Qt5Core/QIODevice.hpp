#ifndef LUACXX_QIODevice_INCLUDED
#define LUACXX_QIODevice_INCLUDED

#include "../stack.hpp"
#include "../enum.hpp"

#include <QIODevice>

#include "QObject.hpp"

LUA_METATABLE_INHERIT(QIODevice, QObject);
LUA_METATABLE_ENUM(QIODevice::OpenModeFlag);

extern "C" int luaopen_Qt5Core_QIODevice(lua_State* const);

#endif // LUACXX_QIODevice_INCLUDED

