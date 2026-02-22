#ifndef luacxx_QPageSize_INCLUDED
#define luacxx_QPageSize_INCLUDED

#include "../stack.hpp"
#include "../enum.hpp"

#include <QPageSize>

LUA_METATABLE_BUILT(QPageSize)
LUA_METATABLE_ENUM(QPageSize::PageSizeId)
LUA_METATABLE_ENUM(QPageSize::SizeMatchPolicy)
LUA_METATABLE_ENUM(QPageSize::Unit)

extern "C" int luaopen_Qt5Gui_QPageSize(lua_State* const);

#endif // luacxx_QPageSize_INCLUDED
