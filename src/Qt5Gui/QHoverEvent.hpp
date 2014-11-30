#ifndef luacxx_QHoverEvent_INCLUDED
#define luacxx_QHoverEvent_INCLUDED

#include "../stack.hpp"

#include <QHoverEvent>

#include "QInputEvent.hpp"

// http://qt-project.org/doc/qt-5/qhoverevent.html

LUA_METATABLE_INHERIT(QHoverEvent, QInputEvent)

extern "C" int luaopen_Qt5Gui_QHoverEvent(lua_State* const);

#endif // luacxx_QHoverEvent_INCLUDED
