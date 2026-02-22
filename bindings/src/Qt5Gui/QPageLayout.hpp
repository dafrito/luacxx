#ifndef luacxx_QPageLayout_INCLUDED
#define luacxx_QPageLayout_INCLUDED

#include "../stack.hpp"
#include "../enum.hpp"

#include <QPageLayout>

LUA_METATABLE_BUILT(QPageLayout)
LUA_METATABLE_ENUM(QPageLayout::Mode)
LUA_METATABLE_ENUM(QPageLayout::Orientation)
LUA_METATABLE_ENUM(QPageLayout::Unit)

extern "C" int luaopen_Qt5Gui_QPageLayout(lua_State* const);

#endif // luacxx_QPageLayout_INCLUDED
