#ifndef luacxx_QExposeEvent_INCLUDED
#define luacxx_QExposeEvent_INCLUDED

#include "../stack.hpp"

#include <QExposeEvent>

#include "../Qt5Core/QEvent.hpp"

// http://qt-project.org/doc/qt-5/qexposeevent.html

LUA_METATABLE_INHERIT(QExposeEvent, QEvent)

extern "C" int luaopen_Qt5Gui_QExposeEvent(lua_State* const);

#endif // luacxx_QExposeEvent_INCLUDED
