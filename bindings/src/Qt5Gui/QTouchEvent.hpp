#ifndef luacxx_QTouchEvent_INCLUDED
#define luacxx_QTouchEvent_INCLUDED

#include "../stack.hpp"

#include <QTouchEvent>

#include "QInputEvent.hpp"

LUA_METATABLE_INHERIT(QTouchEvent, QInputEvent)
LUA_METATABLE_NAMED(QTouchEvent::TouchPoint)

extern "C" int luaopen_Qt5Gui_QTouchEvent(lua_State* const);

#endif // luacxx_QTouchEvent_INCLUDED
