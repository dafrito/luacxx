#ifndef luacxx_QNetworkAccessManager_INCLUDED
#define luacxx_QNetworkAccessManager_INCLUDED

#include "../stack.hpp"
#include "../enum.hpp"

#include <QNetworkAccessManager>

#include "../Qt5Core/QObject.hpp"

// http://doc.qt.io/qt-5/qnetworkaccessmanager.html

LUA_METATABLE_INHERIT(QNetworkAccessManager, QObject)
LUA_METATABLE_ENUM(QNetworkAccessManager::NetworkAccessibility)
LUA_METATABLE_ENUM(QNetworkAccessManager::Operation)

extern "C" int luaopen_Qt5Network_QNetworkAccessManager(lua_State* const);

#endif // luacxx_QNetworkAccessManager_INCLUDED
