#ifndef luacxx_QIconDragEvent_INCLUDED
#define luacxx_QIconDragEvent_INCLUDED

#include "../stack.hpp"

#include <QIconDragEvent>

#include "../Qt5Core/QEvent.hpp"

// http://qt-project.org/doc/qt-5/qicondragevent.html

LUA_METATABLE_INHERIT(QIconDragEvent, QEvent)

extern "C" int luaopen_Qt5Gui_QIconDragEvent(lua_State* const);

#endif // luacxx_QIconDragEvent_INCLUDED
