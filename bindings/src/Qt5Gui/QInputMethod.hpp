#ifndef LUACXX_QINPUTMETHOD_INCLUDED
#define LUACXX_QINPUTMETHOD_INCLUDED

#include "Qt5Gui.hpp"
#include <QInputMethod>

LUA_METATABLE_BUILT(QInputMethod);

extern "C" int luaopen_Qt5Gui_QInputMethod(lua_State* const);

#endif // LUACXX_QINPUTMETHOD_INCLUDED
