#include "QLocalSocket.hpp"
#include "../type/function.hpp"
#include "../thread.hpp"

#include <QLocalSocket>

#include "../Qt5Core/QString.hpp"

// https://qt-project.org/doc/qt-5/qlocalsocket.html

void lua::QLocalSocket_metatable(const lua::index& mt)
{
    lua::QIODevice_metatable(mt);

    mt["abort"] = &QLocalSocket::abort;
    mt["connectToServer"] = QLocalSocket_connectToServer;
    mt["disconnectFromServer"] = &QLocalSocket::disconnectFromServer;
    mt["error"] = &QLocalSocket::error;
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

int QLocalSocket_new(lua::state* const state)
{
    // QLocalSocket(QObject * parent = 0)
    lua::make<QLocalSocket>(state);
    // TODO Set up object-specific methods

    return 1;
}

int luaopen_luacxx_QLocalSocket(lua::state* const state)
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
