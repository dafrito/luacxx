#ifndef luacxx_QTextList_INCLUDED
#define luacxx_QTextList_INCLUDED

#include "../stack.hpp"

#include <QTextList>

LUA_METATABLE_BUILT(QTextList)

extern "C" int luaopen_Qt5Gui_QTextList(lua_State* const);

#endif // luacxx_QTextList_INCLUDED
