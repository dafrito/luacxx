#ifndef luacxx_QStatusTipEvent_INCLUDED
#define luacxx_QStatusTipEvent_INCLUDED

#include "../stack.hpp"

#include <QStatusTipEvent>

#include "../Qt5Core/QEvent.hpp"

// http://qt-project.org/doc/qt-5/qstatustipevent.html

LUA_METATABLE_INHERIT(QStatusTipEvent, QEvent)

extern "C" int luaopen_Qt5Gui_QStatusTipEvent(lua_State* const);

#endif // luacxx_QStatusTipEvent_INCLUDED
