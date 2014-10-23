#ifndef LUA_CXX_QSIZEPOLICY_INCLUDED
#define LUA_CXX_QSIZEPOLICY_INCLUDED

#include "Qt5Widgets.hpp"
#include "../enum.hpp"

#include <QSizePolicy>

LUA_METATABLE_BUILT(QSizePolicy);
LUA_METATABLE_ENUM(QSizePolicy::ControlType);
LUA_METATABLE_ENUM(QSizePolicy::Policy);
LUA_METATABLE_ENUM(QSizePolicy::PolicyFlag);

extern "C" int luaopen_Qt5Widgets_QSizePolicy(lua_State* const);

#endif // LUA_CXX_QSIZEPOLICY_INCLUDED
