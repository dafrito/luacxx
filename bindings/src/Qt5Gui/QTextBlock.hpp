#ifndef luacxx_QTextBlock_INCLUDED
#define luacxx_QTextBlock_INCLUDED

#include "../stack.hpp"

#include <QTextBlock>

LUA_METATABLE_BUILT(QTextBlock)

extern "C" int luaopen_Qt5Gui_QTextBlock(lua_State* const);

#endif // luacxx_QTextBlock_INCLUDED
