#ifndef luacxx_QFocusEvent_INCLUDED
#define luacxx_QFocusEvent_INCLUDED

#include "../stack.hpp"

#include <QFocusEvent>

#include "../Qt5Core/QEvent.hpp"

// http://qt-project.org/doc/qt-5/qfocusevent.html

LUA_METATABLE_INHERIT(QFocusEvent, QEvent)

extern "C" int luaopen_Qt5Gui_QFocusEvent(lua_State* const);

#endif // luacxx_QFocusEvent_INCLUDED
