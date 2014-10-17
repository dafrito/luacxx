#ifndef luacxx_QFileDevice_INCLUDED
#define luacxx_QFileDevice_INCLUDED

#include "Qt5Core.hpp"

class QFileDevice;

LUA_METATABLE_BUILT(QFileDevice)

extern "C" int luaopen_Qt5Core_QFileDevice(lua_State* const);

#endif // luacxx_QFileDevice_INCLUDED
