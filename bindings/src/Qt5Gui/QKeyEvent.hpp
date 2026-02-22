#ifndef luacxx_QKeyEvent_INCLUDED
#define luacxx_QKeyEvent_INCLUDED

#include "../stack.hpp"

#include <QKeyEvent>

#include "QInputEvent.hpp"

// http://qt-project.org/doc/qt-5/qkeyevent.html

LUA_METATABLE_INHERIT(QKeyEvent, QInputEvent)

extern "C" int luaopen_Qt5Gui_QKeyEvent(lua_State* const);

#endif // luacxx_QKeyEvent_INCLUDED
