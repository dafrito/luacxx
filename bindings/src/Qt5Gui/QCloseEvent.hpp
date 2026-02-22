#ifndef luacxx_QCloseEvent_INCLUDED
#define luacxx_QCloseEvent_INCLUDED

#include "../stack.hpp"

#include <QCloseEvent>

#include "../Qt5Core/QEvent.hpp"

// http://qt-project.org/doc/qt-5/qcloseevent.html

LUA_METATABLE_INHERIT(QCloseEvent, QEvent)

extern "C" int luaopen_Qt5Gui_QCloseEvent(lua_State* const);

#endif // luacxx_QCloseEvent_INCLUDED
