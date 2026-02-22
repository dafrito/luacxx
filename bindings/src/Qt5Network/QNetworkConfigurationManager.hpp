#ifndef luacxx_QNetworkConfigurationManager_INCLUDED
#define luacxx_QNetworkConfigurationManager_INCLUDED

#include "../stack.hpp"

#include <QNetworkConfigurationManager>

LUA_METATABLE_BUILT(QNetworkConfigurationManager)

extern "C" int luaopen_luacxx_QNetworkConfigurationManager(lua_State* const);

#endif // luacxx_QNetworkConfigurationManager_INCLUDED
