#ifndef luacxx_QScrollEvent_INCLUDED
#define luacxx_QScrollEvent_INCLUDED

#include "../stack.hpp"
#include "../enum.hpp"

#include <QScrollEvent>

#include "../Qt5Core/QEvent.hpp"

// http://qt-project.org/doc/qt-5/qscrollevent.html

LUA_METATABLE_INHERIT(QScrollEvent, QEvent)
LUA_METATABLE_ENUM(QScrollEvent::ScrollState)

extern "C" int luaopen_Qt5Gui_QScrollEvent(lua_State* const);

#endif // luacxx_QScrollEvent_INCLUDED
