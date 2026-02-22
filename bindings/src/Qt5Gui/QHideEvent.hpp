#ifndef luacxx_QHideEvent_INCLUDED
#define luacxx_QHideEvent_INCLUDED

#include "../stack.hpp"

#include <QHideEvent>

#include "../Qt5Core/QEvent.hpp"

// http://qt-project.org/doc/qt-5/qhideevent.html

LUA_METATABLE_INHERIT(QHideEvent, QEvent)

extern "C" int luaopen_Qt5Gui_QHideEvent(lua_State* const);

#endif // luacxx_QHideEvent_INCLUDED
