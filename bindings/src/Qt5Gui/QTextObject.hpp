#ifndef luacxx_QTextObject_INCLUDED
#define luacxx_QTextObject_INCLUDED

#include "../stack.hpp"
#include "../Qt5Core/QObject.hpp"

#include <QTextObject>

LUA_METATABLE_INHERIT(QTextObject, QObject)

extern "C" int luaopen_Qt5Gui_QTextObject(lua_State* const);

#endif // luacxx_QTextObject_INCLUDED
