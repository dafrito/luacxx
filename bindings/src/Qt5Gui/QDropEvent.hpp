#ifndef luacxx_QDropEvent_INCLUDED
#define luacxx_QDropEvent_INCLUDED

#include "../stack.hpp"

#include <QDropEvent>

#include "../Qt5Core/QEvent.hpp"

// http://qt-project.org/doc/qt-5/qdropevent.html

LUA_METATABLE_INHERIT(QDropEvent, QEvent)

extern "C" int luaopen_Qt5Gui_QDropEvent(lua_State* const);

#endif // luacxx_QDropEvent_INCLUDED
