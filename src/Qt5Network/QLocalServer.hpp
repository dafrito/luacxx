#ifndef luacxx_QLocalServer_INCLUDED
#define luacxx_QLocalServer_INCLUDED

#include "../stack.hpp"
#include "../enum.hpp"

#include <QLocalServer>

#include "../Qt5Core/QObject.hpp"

// http://qt-project.org/doc/qt-5/qlocalserver.html#details

LUA_METATABLE_INHERIT(QLocalServer, QObject)
LUA_METATABLE_ENUM(QLocalServer::SocketOption)

extern "C" int luaopen_Qt5Network_QLocalServer(lua_State* const);

#endif // luacxx_QLocalServer_INCLUDED
