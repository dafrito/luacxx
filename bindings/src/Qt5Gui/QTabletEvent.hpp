#ifndef luacxx_QTabletEvent_INCLUDED
#define luacxx_QTabletEvent_INCLUDED

#include "../stack.hpp"
#include "../enum.hpp"

#include <QTabletEvent>

#include "QInputEvent.hpp"

// http://qt-project.org/doc/qt-5/qtabletevent.html

LUA_METATABLE_INHERIT(QTabletEvent, QInputEvent)
LUA_METATABLE_ENUM(QTabletEvent::PointerType)
LUA_METATABLE_ENUM(QTabletEvent::TabletDevice)

extern "C" int luaopen_Qt5Gui_QTabletEvent(lua_State* const);

#endif // luacxx_QTabletEvent_INCLUDED
