#ifndef luacxx_QTextLayout_INCLUDED
#define luacxx_QTextLayout_INCLUDED

#include "../stack.hpp"
#include "../enum.hpp"

#include <QTextLayout>

LUA_METATABLE_BUILT(QTextLayout)
LUA_METATABLE_ENUM(QTextLayout::CursorMode)
LUA_METATABLE_NAMED(QTextLayout::FormatRange)

extern "C" int luaopen_Qt5Gui_QTextLayout(lua_State* const);

#endif // luacxx_QTextLayout_INCLUDED
