#ifndef luacxx_QFileDevice_INCLUDED
#define luacxx_QFileDevice_INCLUDED

#include "Qt5Core.hpp"
#include "../enum.hpp"

#include "QIODevice.hpp"

#include <QFileDevice>

LUA_METATABLE_INHERIT(QFileDevice, QIODevice);

LUA_METATABLE_ENUM(QFileDevice::MemoryMapFlags)
LUA_METATABLE_ENUM(QFileDevice::Permission)
LUA_METATABLE_ENUM(QFileDevice::FileError)
LUA_METATABLE_ENUM(QFileDevice::FileHandleFlag)

extern "C" int luaopen_Qt5Core_QFileDevice(lua_State* const);

#endif // luacxx_QFileDevice_INCLUDED
