#include "QLocalSocket.hpp"
#include "../thread.hpp"

#include "../Qt5Core/QString.hpp"
#include "../Qt5Core/QObject.hpp"
#include "../Qt5Core/QIODevice.hpp"

// https://qt-project.org/doc/qt-5/qlocalsocket.html

int QLocalSocket_connectToServer(lua_State* const state)
{
    return 0;
}
int QLocalSocket_error(lua_State* const state)
{
    return 0;
}
int QLocalSocket_open(lua_State* const state)
{
    return 0;
}
int QLocalSocket_setSocketDescriptor(lua_State* const state)
{
    return 0;
}
int QLocalSocket_waitForConnected(lua_State* const state)
{
    return 0;
}
int QLocalSocket_waitForDisconnected(lua_State* const state)
{
    return 0;
}

void lua::QLocalSocket_metatable(lua_State* const state, const int pos)
{
    lua::QIODevice_metatable(state, pos);

    lua::index mt(state, pos);
    mt["abort"] = &QLocalSocket::abort;
    mt["connectToServer"] = QLocalSocket_connectToServer;
    mt["disconnectFromServer"] = &QLocalSocket::disconnectFromServer;
    mt["error"] = QLocalSocket_error;
    mt["flush"] = &QLocalSocket::flush;
    mt["fullServerName"] = &QLocalSocket::fullServerName;
    mt["isValid"] = &QLocalSocket::isValid;
    mt["open"] = QLocalSocket_open;
    mt["readBufferSize"] = &QLocalSocket::readBufferSize;
    mt["serverName"] = &QLocalSocket::serverName;
    mt["setReadBufferSize"] = &QLocalSocket::setReadBufferSize;
    mt["setServerName"] = &QLocalSocket::setServerName;
    mt["setSocketDescriptor"] = QLocalSocket_setSocketDescriptor;
    mt["socketDescriptor"] = &QLocalSocket::socketDescriptor;
    mt["state"] = &QLocalSocket::state;
    mt["waitForConnected"] = QLocalSocket_waitForConnected;
    mt["waitForDisconnected"] = QLocalSocket_waitForDisconnected;
}

int QLocalSocket_new(lua_State* const state)
{
    if (lua_gettop(state) == 1) {
        // QLocalSocket(QObject * parent)
        lua::push(state, new QLocalSocket(lua::get<QObject*>(state, 1)));
    } else {
        // QLocalSocket()
        lua::push(state, new QLocalSocket);
    }
    return 1;
}

int luaopen_Qt5Network_QLocalSocket(lua_State* const state)
{
    lua::thread env(state);

    env["QLocalSocket"] = lua::value::table;
    env["QLocalSocket"]["new"] = QLocalSocket_new;
    auto t = env["QLocalSocket"];

    // enum QLocalSocket::LocalSocketError
    t["ConnectionRefusedError"] = QLocalSocket::ConnectionRefusedError;
    t["PeerClosedError"] = QLocalSocket::PeerClosedError;
    t["ServerNotFoundError"] = QLocalSocket::ServerNotFoundError;
    t["SocketAccessError"] = QLocalSocket::SocketAccessError;
    t["SocketResourceError"] = QLocalSocket::SocketResourceError;
    t["SocketTimeoutError"] = QLocalSocket::SocketTimeoutError;
    t["DatagramTooLargeError"] = QLocalSocket::DatagramTooLargeError;
    t["ConnectionError"] = QLocalSocket::ConnectionError;
    t["UnsupportedSocketOperationError"] = QLocalSocket::UnsupportedSocketOperationError;
    t["OperationError"] = QLocalSocket::OperationError;
    t["UnknownSocketError"] = QLocalSocket::UnknownSocketError;

    // enum QLocalSocket::LocalSocketState
    t["UnconnectedState"] = QLocalSocket::UnconnectedState;
    t["ConnectingState"] = QLocalSocket::ConnectingState;
    t["ConnectedState"] = QLocalSocket::ConnectedState;
    t["ClosingState"] = QLocalSocket::ClosingState;

    return 0;
}
