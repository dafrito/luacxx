#ifndef luacxx_QTcpServer_INCLUDED
#define luacxx_QTcpServer_INCLUDED

#include "../stack.hpp"

#include <QTcpServer>

#include "../Qt5Core/QObject.hpp"

// http://qt-project.org/doc/qt-5/qtcpserver.html

LUA_METATABLE_INHERIT(QTcpServer, QObject)

extern "C" int luaopen_Qt5Network_QTcpServer(lua_State* const);

#endif // luacxx_QTcpServer_INCLUDED
