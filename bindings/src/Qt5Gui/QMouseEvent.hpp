#ifndef luacxx_QMouseEvent_INCLUDED
#define luacxx_QMouseEvent_INCLUDED

#include "../stack.hpp"

#include <QMouseEvent>

#include "QInputEvent.hpp"

// http://qt-project.org/doc/qt-5/qmouseevent.html

LUA_METATABLE_INHERIT(QMouseEvent, QInputEvent)

extern "C" int luaopen_Qt5Gui_QMouseEvent(lua_State* const);

#endif // luacxx_QMouseEvent_INCLUDED
