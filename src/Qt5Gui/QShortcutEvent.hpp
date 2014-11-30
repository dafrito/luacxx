#ifndef luacxx_QShortcutEvent_INCLUDED
#define luacxx_QShortcutEvent_INCLUDED

#include "../stack.hpp"

#include <QShortcutEvent>

#include "../Qt5Core/QEvent.hpp"

// http://qt-project.org/doc/qt-5/qshortcutevent.html

LUA_METATABLE_INHERIT(QShortcutEvent, QEvent)

extern "C" int luaopen_Qt5Gui_QShortcutEvent(lua_State* const);

#endif // luacxx_QShortcutEvent_INCLUDED
