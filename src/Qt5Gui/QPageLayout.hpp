#ifndef luacxx_QPageLayout_INCLUDED
#define luacxx_QPageLayout_INCLUDED

#include "../stack.hpp"

#include <QPageLayout>

LUA_METATABLE_BUILT(QPageLayout)

extern "C" int luaopen_luacxx_QPageLayout(lua_State* const);

#endif // luacxx_QPageLayout_INCLUDED
