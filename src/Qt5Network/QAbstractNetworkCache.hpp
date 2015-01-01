#ifndef luacxx_QAbstractNetworkCache_INCLUDED
#define luacxx_QAbstractNetworkCache_INCLUDED

#include "../stack.hpp"

#include <QAbstractNetworkCache>

#include "../Qt5Core/QObject.hpp"

// http://qt-project.org/doc/qt-5/qabstractnetworkcache.html

LUA_METATABLE_INHERIT(QAbstractNetworkCache, QObject)

extern "C" int luaopen_Qt5Network_QAbstractNetworkCache(lua_State* const);

#endif // luacxx_QAbstractNetworkCache_INCLUDED
