#include "QTcpServer.hpp"
#include "../convert/callable.hpp"
#include "../convert/const_char_p.hpp"
#include "../thread.hpp"

#include "../Qt5Core/QString.hpp"
#include "QNetworkProxy.hpp"
#include "QHostAddress.hpp"
#include "QAbstractSocket.hpp"
#include "QTcpSocket.hpp"

int QTcpServer_listen(lua_State* const state)
{
    auto self = lua::get<QTcpServer*>(state, 1);

    // bool     listen(const QHostAddress & address = QHostAddress::Any, quint16 port = 0)
    switch (lua_gettop(state)) {
    case 1:
        lua::push(state, self->listen());
        break;
    case 2:
        lua::push(state, self->listen(
            lua::get<const QHostAddress&>(state, 2)
        ));
        break;
    case 3:
    default:
        lua::push(state, self->listen(
            lua::get<const QHostAddress&>(state, 2),
            lua::get<quint16>(state, 3)
        ));
        break;
    }

    return 1;
}

int QTcpServer_waitForNewConnection(lua_State* const state)
{
    auto self = lua::get<QTcpServer*>(state, 1);

    // bool waitForNewConnection(int msec = 0, bool * timedOut = 0)
    switch (lua_gettop(state)) {
    case 1:
        lua::push(state, self->waitForNewConnection());
        break;
    case 2:
    {
        bool timedOut;
        lua::push(state, self->waitForNewConnection(
            lua::get<int>(state, 2),
            &timedOut
        ));
        lua::push(state, timedOut);
        return 2;
    }
    case 3:
    default:
        lua::push(state, self->waitForNewConnection(
            lua::get<int>(state, 2),
            lua::get<bool*>(state, 3)
        ));
        break;
    }

    return 1;
}

namespace lua {

void QTcpServer_metatable(lua_State* const state, const int pos)
{
    lua::QObject_metatable(state, pos);

    lua::index mt(state, pos);
    mt["close"] = &QTcpServer::close;
    mt["errorString"] = &QTcpServer::errorString;
    mt["hasPendingConnections"] = &QTcpServer::hasPendingConnections;
    mt["isListening"] = &QTcpServer::isListening;
    mt["listen"] = QTcpServer_listen;
    mt["maxPendingConnections"] = &QTcpServer::maxPendingConnections;
    mt["nextPendingConnection"] = &QTcpServer::nextPendingConnection;
    mt["pauseAccepting"] = &QTcpServer::pauseAccepting;
    mt["proxy"] = &QTcpServer::proxy;
    mt["resumeAccepting"] = &QTcpServer::resumeAccepting;
    mt["serverAddress"] = &QTcpServer::serverAddress;
    mt["serverError"] = &QTcpServer::serverError;
    mt["serverPort"] = &QTcpServer::serverPort;
    mt["setMaxPendingConnections"] = &QTcpServer::setMaxPendingConnections;
    mt["setProxy"] = &QTcpServer::setProxy;
    mt["setSocketDescriptor"] = &QTcpServer::setSocketDescriptor;
    mt["socketDescriptor"] = &QTcpServer::socketDescriptor;
    mt["waitForNewConnection"] = QTcpServer_waitForNewConnection;
}

} // namespace lua

int QTcpServer_new(lua_State* const state)
{
    if (lua_gettop(state) == 0) {
        lua::push(state, new QTcpServer);
    } else {
        lua::push(state, new QTcpServer(
            lua::get<QObject*>(state, 1)
        ));
    }

    return 1;
}

int luaopen_Qt5Network_QTcpServer(lua_State* const state)
{
    lua::thread env(state);

    env["QTcpServer"] = lua::value::table;
    env["QTcpServer"]["new"] = QTcpServer_new;
    auto t = env["QTcpServer"];

    return 0;
}
