#ifndef luacxx_QActionEvent_INCLUDED
#define luacxx_QActionEvent_INCLUDED

#include "../stack.hpp"

#include <QActionEvent>

#include "../Qt5Core/QEvent.hpp"

// http://qt-project.org/doc/qt-5/qactionevent.html

LUA_METATABLE_INHERIT(QActionEvent, QEvent)

extern "C" int luaopen_Qt5Gui_QActionEvent(lua_State* const);

#endif // luacxx_QActionEvent_INCLUDED
