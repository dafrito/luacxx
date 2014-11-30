#ifndef luacxx_QInputMethodQueryEvent_INCLUDED
#define luacxx_QInputMethodQueryEvent_INCLUDED

#include "../stack.hpp"

#include <QInputMethodQueryEvent>

#include "../Qt5Core/QEvent.hpp"

// http://qt-project.org/doc/qt-5/qinputmethodqueryevent.html

LUA_METATABLE_INHERIT(QInputMethodQueryEvent, QEvent)

extern "C" int luaopen_Qt5Gui_QInputMethodQueryEvent(lua_State* const);

#endif // luacxx_QInputMethodQueryEvent_INCLUDED
