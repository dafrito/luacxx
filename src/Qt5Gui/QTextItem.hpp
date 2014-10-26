#ifndef luacxx_QTextItem_INCLUDED
#define luacxx_QTextItem_INCLUDED

#include "../stack.hpp"
#include "../enum.hpp"

#include <QTextItem>

LUA_METATABLE_BUILT(QTextItem)
LUA_METATABLE_ENUM(QTextItem::RenderFlag)

extern "C" int luaopen_Qt5Gui_QTextItem(lua_State* const);

#endif // luacxx_QTextItem_INCLUDED
