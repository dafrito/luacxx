#ifndef luacxx_QWhatsThisClickedEvent_INCLUDED
#define luacxx_QWhatsThisClickedEvent_INCLUDED

#include "../stack.hpp"

#include <QWhatsThisClickedEvent>

#include "../Qt5Core/QEvent.hpp"

// http://qt-project.org/doc/qt-5/qwhatsthisclickedevent.html

LUA_METATABLE_INHERIT(QWhatsThisClickedEvent, QEvent)

extern "C" int luaopen_Qt5Gui_QWhatsThisClickedEvent(lua_State* const);

#endif // luacxx_QWhatsThisClickedEvent_INCLUDED
