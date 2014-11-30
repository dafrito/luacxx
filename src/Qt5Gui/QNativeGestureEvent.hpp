#ifndef luacxx_QNativeGestureEvent_INCLUDED
#define luacxx_QNativeGestureEvent_INCLUDED

#include "../stack.hpp"

#include <QNativeGestureEvent>

#include "QInputEvent.hpp"

// http://qt-project.org/doc/qt-5/qnativegestureevent.html

LUA_METATABLE_INHERIT(QNativeGestureEvent, QInputEvent)

extern "C" int luaopen_Qt5Gui_QNativeGestureEvent(lua_State* const);

#endif // luacxx_QNativeGestureEvent_INCLUDED
