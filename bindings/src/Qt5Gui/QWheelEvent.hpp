#ifndef luacxx_QWheelEvent_INCLUDED
#define luacxx_QWheelEvent_INCLUDED

#include "../stack.hpp"

#include <QWheelEvent>

#include "QInputEvent.hpp"

// http://qt-project.org/doc/qt-5/qwheelevent.html

LUA_METATABLE_INHERIT(QWheelEvent, QInputEvent)

extern "C" int luaopen_Qt5Gui_QWheelEvent(lua_State* const);

#endif // luacxx_QWheelEvent_INCLUDED
