#ifndef luacxx_QScrollPrepareEvent_INCLUDED
#define luacxx_QScrollPrepareEvent_INCLUDED

#include "../stack.hpp"

#include <QScrollPrepareEvent>

#include "../Qt5Core/QEvent.hpp"

// http://qt-project.org/doc/qt-5/qscrollprepareevent.html

LUA_METATABLE_INHERIT(QScrollPrepareEvent, QEvent)

extern "C" int luaopen_Qt5Gui_QScrollPrepareEvent(lua_State* const);

#endif // luacxx_QScrollPrepareEvent_INCLUDED
