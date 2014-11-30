#ifndef luacxx_QEnterEvent_INCLUDED
#define luacxx_QEnterEvent_INCLUDED

#include "../stack.hpp"

#include <QEnterEvent>

#include "../Qt5Core/QEvent.hpp"

// http://qt-project.org/doc/qt-5/qenterevent.html

LUA_METATABLE_INHERIT(QEnterEvent, QEvent)

extern "C" int luaopen_Qt5Gui_QEnterEvent(lua_State* const);

#endif // luacxx_QEnterEvent_INCLUDED
