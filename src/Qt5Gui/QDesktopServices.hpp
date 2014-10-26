#ifndef luacxx_QDesktopServices_INCLUDED
#define luacxx_QDesktopServices_INCLUDED

#include "../stack.hpp"

#include <QDesktopServices>

LUA_METATABLE_BUILT(QDesktopServices)

extern "C" int luaopen_Qt5Gui_QDesktopServices(lua_State* const);

#endif // luacxx_QDesktopServices_INCLUDED
