#ifndef luacxx_QDragEnterEvent_INCLUDED
#define luacxx_QDragEnterEvent_INCLUDED

#include "../stack.hpp"

#include <QDragEnterEvent>

#include "QDragMoveEvent.hpp"

// http://qt-project.org/doc/qt-5/qdragenterevent.html

LUA_METATABLE_INHERIT(QDragEnterEvent, QDragMoveEvent)

extern "C" int luaopen_Qt5Gui_QDragEnterEvent(lua_State* const);

#endif // luacxx_QDragEnterEvent_INCLUDED
