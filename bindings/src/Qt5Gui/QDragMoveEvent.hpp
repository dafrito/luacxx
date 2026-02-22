#ifndef luacxx_QDragMoveEvent_INCLUDED
#define luacxx_QDragMoveEvent_INCLUDED

#include "../stack.hpp"

#include <QDragMoveEvent>

#include "QDropEvent.hpp"

// http://qt-project.org/doc/qt-5/qdragmoveevent.html

LUA_METATABLE_INHERIT(QDragMoveEvent, QDropEvent)

extern "C" int luaopen_Qt5Gui_QDragMoveEvent(lua_State* const);

#endif // luacxx_QDragMoveEvent_INCLUDED
