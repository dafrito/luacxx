#ifndef luacxx_QTextObject_INCLUDED
#define luacxx_QTextObject_INCLUDED

#include "../stack.hpp"

#include <QTextObject>

LUA_METATABLE_BUILT(QTextObject)

extern "C" int luaopen_Qt5Gui_QTextObject(lua_State* const);

#endif // luacxx_QTextObject_INCLUDED
