#ifndef luacxx_QPaintEvent_INCLUDED
#define luacxx_QPaintEvent_INCLUDED

#include "../stack.hpp"

#include <QPaintEvent>

#include "../Qt5Core/QEvent.hpp"

// http://qt-project.org/doc/qt-5/qpaintevent.html

LUA_METATABLE_INHERIT(QPaintEvent, QEvent)

extern "C" int luaopen_Qt5Gui_QPaintEvent(lua_State* const);

#endif // luacxx_QPaintEvent_INCLUDED
