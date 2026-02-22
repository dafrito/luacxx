#ifndef luacxx_QInputEvent_INCLUDED
#define luacxx_QInputEvent_INCLUDED

#include "../stack.hpp"

#include <QInputEvent>

#include "../Qt5Core/QEvent.hpp"

// http://qt-project.org/doc/qt-5/qinputevent.html

LUA_METATABLE_INHERIT(QInputEvent, QEvent)

extern "C" int luaopen_Qt5Gui_QInputEvent(lua_State* const);

#endif // luacxx_QInputEvent_INCLUDED
