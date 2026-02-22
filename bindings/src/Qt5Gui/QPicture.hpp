#ifndef luacxx_QPicture_INCLUDED
#define luacxx_QPicture_INCLUDED

#include "../stack.hpp"

#include <QPicture>

#include "QPaintDevice.hpp"

LUA_METATABLE_INHERIT(QPicture, QPaintDevice)

extern "C" int luaopen_Qt5Gui_QPicture(lua_State* const);

#endif // luacxx_QPicture_INCLUDED
