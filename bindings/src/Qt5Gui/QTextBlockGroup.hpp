#ifndef luacxx_QTextBlockGroup_INCLUDED
#define luacxx_QTextBlockGroup_INCLUDED

#include "../stack.hpp"
#include "QTextObject.hpp"

#include <QTextBlockGroup>

LUA_METATABLE_INHERIT(QTextBlockGroup, QTextObject);

extern "C" int luaopen_Qt5Gui_QTextBlockGroup(lua_State* const);

#endif // luacxx_QTextBlockGroup_INCLUDED
