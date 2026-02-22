#ifndef luacxx_QWindowStateChangeEvent_INCLUDED
#define luacxx_QWindowStateChangeEvent_INCLUDED

#include "../stack.hpp"

#include <QWindowStateChangeEvent>

#include "../Qt5Core/QEvent.hpp"

// http://qt-project.org/doc/qt-5/qwindowstatechangeevent.html

LUA_METATABLE_INHERIT(QWindowStateChangeEvent, QEvent)

extern "C" int luaopen_Qt5Gui_QWindowStateChangeEvent(lua_State* const);

#endif // luacxx_QWindowStateChangeEvent_INCLUDED
