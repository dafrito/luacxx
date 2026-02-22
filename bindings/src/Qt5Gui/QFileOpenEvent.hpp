#ifndef luacxx_QFileOpenEvent_INCLUDED
#define luacxx_QFileOpenEvent_INCLUDED

#include "../stack.hpp"

#include <QFileOpenEvent>

#include "../Qt5Core/QEvent.hpp"

// http://qt-project.org/doc/qt-5/qfileopenevent.html

LUA_METATABLE_INHERIT(QFileOpenEvent, QEvent);

extern "C" int luaopen_Qt5Gui_QFileOpenEvent(lua_State* const);

#endif // luacxx_QFileOpenEvent_INCLUDED
