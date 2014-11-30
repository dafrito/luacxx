#ifndef luacxx_QDragLeaveEvent_INCLUDED
#define luacxx_QDragLeaveEvent_INCLUDED

#include "../stack.hpp"

#include <QDragLeaveEvent>

#include "../Qt5Core/QEvent.hpp"

// http://qt-project.org/doc/qt-5/qdragleaveevent.html

LUA_METATABLE_INHERIT(QDragLeaveEvent, QEvent)

extern "C" int luaopen_Qt5Gui_QDragLeaveEvent(lua_State* const);

#endif // luacxx_QDragLeaveEvent_INCLUDED
