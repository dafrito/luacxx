#ifndef luacxx_QShowEvent_INCLUDED
#define luacxx_QShowEvent_INCLUDED

#include "../stack.hpp"

#include <QShowEvent>

#include "../Qt5Core/QEvent.hpp"

// http://qt-project.org/doc/qt-5/qshowevent.html

LUA_METATABLE_INHERIT(QShowEvent, QEvent)

extern "C" int luaopen_Qt5Gui_QShowEvent(lua_State* const);

#endif // luacxx_QShowEvent_INCLUDED
