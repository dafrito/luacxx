#ifndef luacxx_QResizeEvent_INCLUDED
#define luacxx_QResizeEvent_INCLUDED

#include "../stack.hpp"

#include <QResizeEvent>

#include "../Qt5Core/QEvent.hpp"

// http://qt-project.org/doc/qt-5/qresizeevent.html

LUA_METATABLE_INHERIT(QResizeEvent, QEvent)

extern "C" int luaopen_Qt5Gui_QResizeEvent(lua_State* const);

#endif // luacxx_QResizeEvent_INCLUDED
