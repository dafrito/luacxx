#ifndef luacxx_QNetworkInterface_INCLUDED
#define luacxx_QNetworkInterface_INCLUDED

#include "Qt5Network.hpp"
#include "../enum.hpp"

#include <QNetworkInterface>

LUA_METATABLE_BUILT(QNetworkInterface);
LUA_METATABLE_ENUM(QNetworkInterface::InterfaceFlag);

bool operator==(const QNetworkInterface& first, const QNetworkInterface& second);

extern "C" int luaopen_Qt5Network_QNetworkInterface(lua_State* const);

#endif // luacxx_QNetworkInterface_INCLUDED
