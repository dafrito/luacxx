#ifndef luacxx_QMoveEvent_INCLUDED
#define luacxx_QMoveEvent_INCLUDED

#include "../stack.hpp"

#include <QMoveEvent>

#include "../Qt5Core/QEvent.hpp"

// http://qt-project.org/doc/qt-5/qmoveevent.html

LUA_METATABLE_INHERIT(QMoveEvent, QEvent)

extern "C" int luaopen_Qt5Gui_QMoveEvent(lua_State* const);

#endif // luacxx_QMoveEvent_INCLUDED
