#ifndef LUA_CXX_QSIZEPOLICY_INCLUDED
#define LUA_CXX_QSIZEPOLICY_INCLUDED

#include "Qt5Widgets.hpp"

class QSizePolicy;

LUA_METATABLE_BUILT(QSizePolicy);

extern "C" int luaopen_Qt5Widgets_QSizePolicy(lua_State* const);

#endif // LUA_CXX_QSIZEPOLICY_INCLUDED
