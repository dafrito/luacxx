#ifndef luacxx_QHostAddress_INCLUDED
#define luacxx_QHostAddress_INCLUDED

#include "Qt5Network.hpp"
#include "../enum.hpp"

#include <QHostAddress>

namespace lua {

void Q_IPV6ADDR_metatable(lua_State* const state, const int pos);

}; // namespace lua

LUA_METATABLE_BUILT(QHostAddress);
LUA_METATABLE_BUILT_WITH(Q_IPV6ADDR, Q_IPV6ADDR_metatable);
LUA_METATABLE_ENUM(QHostAddress::SpecialAddress);

extern "C" int luaopen_luacxx_QHostAddress(lua_State* const);

#endif // luacxx_QHostAddress_INCLUDED
