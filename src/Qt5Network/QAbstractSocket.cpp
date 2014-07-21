#include "QAbstractSocket.hpp"
#include "../convert/callable.hpp"
#include "../thread.hpp"
#include "QIODevice.hpp"

#include <QAbstractSocket>

// https://qt-project.org/doc/qt-5/qabstractsocket.html

int QAbstractSocket_bind(lua_State* const state)
{
    return 0;
}

int QAbstractSocket_connectToHost(lua_State* const state)
{
    return 0;
}

int QAbstractSocket_setSocketDescriptor(lua_State* const state)
{
    return 0;
}

int QAbstractSocket_waitForConnected(lua_State* const state)
{
    auto self = lua::get<QAbstractSocket*>(state, 1);
    if (lua_gettop(state) > 1) {
        self->waitForConnected(lua::get<int>(state, 2));
    } else {
        self->waitForConnected();
    }
    return 0;
}

int QAbstractSocket_waitForDisconnected(lua_State* const state)
{
    auto self = lua::get<QAbstractSocket*>(state, 1);
    if (lua_gettop(state) > 1) {
        self->waitForDisconnected(lua::get<int>(state, 2));
    } else {
        self->waitForConnected();
    }
    return 0;
}

void lua::QAbstractSocket_metatable(const lua::index& mt)
{
    lua::QIODevice_metatable(mt);

    mt["abort"] = &QAbstractSocket::abort;
    mt["bind"] = QAbstractSocket_bind;
    mt["connectToHost"] = QAbstractSocket_connectToHost;
    mt["disconnectFromHost"] = &QAbstractSocket::disconnectFromHost;
    mt["error"] = &QAbstractSocket::error;
    mt["flush"] = &QAbstractSocket::flush;
    mt["isValid"] = &QAbstractSocket::isValid;
    mt["localAddress"] = &QAbstractSocket::localAddress;
    mt["localPort"] = &QAbstractSocket::localPort;
    mt["pauseMode"] = &QAbstractSocket::pauseMode;
    mt["peerAddress"] = &QAbstractSocket::peerAddress;
    mt["peerName"] = &QAbstractSocket::peerName;
    mt["peerPort"] = &QAbstractSocket::peerPort;
    mt["proxy"] = &QAbstractSocket::proxy;
    mt["readBufferSize"] = &QAbstractSocket::readBufferSize;
    mt["resume"] = &QAbstractSocket::resume;
    mt["setPauseMode"] = &QAbstractSocket::setPauseMode;
    mt["setProxy"] = &QAbstractSocket::setProxy;
    mt["setReadBufferSize"] = &QAbstractSocket::setReadBufferSize;
    mt["setSocketDescriptor"] = QAbstractSocket_setSocketDescriptor;
    mt["setSocketOption"] = &QAbstractSocket::setSocketOption;
    mt["socketDescriptor"] = &QAbstractSocket::socketDescriptor;
    mt["socketOption"] = &QAbstractSocket::socketOption;
    mt["socketType"] = &QAbstractSocket::socketType;
    mt["state"] = &QAbstractSocket::state;
    mt["waitForConnected"] = QAbstractSocket_waitForConnected;
    mt["waitForDisconnected"] = QAbstractSocket_waitForDisconnected;
}

int QAbstractSocket_new(lua_State* const state)
{
    lua::make<QAbstractSocket>(state);
    // TODO Set up object-specific methods

    return 1;
}

int luaopen_luacxx_QAbstractSocket(lua_State* const state)
{
    lua::thread env(state);

    env["QAbstractSocket"] = lua::value::table;
    env["QAbstractSocket"]["new"] = QAbstractSocket_new;

    // enum QAbstractSocket::BindFlag
    // flags QAbstractSocket::BindMode
    t["ShareAddress"] = QAbstractSocket::ShareAddress;
    t["DontShareAddress"] = QAbstractSocket::DontShareAddress;
    t["ReuseAddressHint"] = QAbstractSocket::ReuseAddressHint;
    t["DefaultForPlatform"] = QAbstractSocket::DefaultForPlatform;

    // enum QAbstractSocket::NetworkLayerProtocol
    t["IPv4Protocol"] = QAbstractSocket::IPv4Protocol;
    t["IPv6Protocol"] = QAbstractSocket::IPv6Protocol;
    t["AnyIPProtocol"] = QAbstractSocket::AnyIPProtocol;
    t["UnknownNetworkLayerProtocol"] = QAbstractSocket::UnknownNetworkLayerProtocol;

    // enum QAbstractSocket::PauseMode
    // flags QAbstractSocket::PauseModes
    t["PauseNever"] = QAbstractSocket::PauseNever;
    t["PauseOnSslErrors"] = QAbstractSocket::PauseOnSslErrors;

    // enum QAbstractSocket::SocketError
    t["ConnectionRefusedError"] = QAbstractSocket::ConnectionRefusedError;
    t["RemoteHostClosedError"] = QAbstractSocket::RemoteHostClosedError;
    t["HostNotFoundError"] = QAbstractSocket::HostNotFoundError;
    t["SocketAccessError"] = QAbstractSocket::SocketAccessError;
    t["SocketResourceError"] = QAbstractSocket::SocketResourceError;
    t["SocketTimeoutError"] = QAbstractSocket::SocketTimeoutError;
    t["DatagramTooLargeError"] = QAbstractSocket::DatagramTooLargeError;
    t["NetworkError"] = QAbstractSocket::NetworkError;
    t["AddressInUseError"] = QAbstractSocket::AddressInUseError;
    t["SocketAddressNotAvailableError"] = QAbstractSocket::SocketAddressNotAvailableError;
    t["UnsupportedSocketOperationError"] = QAbstractSocket::UnsupportedSocketOperationError;
    t["ProxyAuthenticationRequiredError"] = QAbstractSocket::ProxyAuthenticationRequiredError;
    t["SslHandshakeFailedError"] = QAbstractSocket::SslHandshakeFailedError;
    t["UnfinishedSocketOperationError"] = QAbstractSocket::UnfinishedSocketOperationError;
    t["ProxyConnectionRefusedError"] = QAbstractSocket::ProxyConnectionRefusedError;
    t["ProxyConnectionClosedError"] = QAbstractSocket::ProxyConnectionClosedError;
    t["ProxyConnectionTimeoutError"] = QAbstractSocket::ProxyConnectionTimeoutError;
    t["ProxyNotFoundError"] = QAbstractSocket::ProxyNotFoundError;
    t["ProxyProtocolError"] = QAbstractSocket::ProxyProtocolError;
    t["OperationError"] = QAbstractSocket::OperationError;
    t["SslInternalError"] = QAbstractSocket::SslInternalError;
    t["SslInvalidUserDataError"] = QAbstractSocket::SslInvalidUserDataError;
    t["TemporaryError"] = QAbstractSocket::TemporaryError;
    t["UnknownSocketError"] = QAbstractSocket::UnknownSocketError;

    // enum QAbstractSocket::SocketOption
    t["LowDelayOption"] = QAbstractSocket::LowDelayOption;
    t["KeepAliveOption"] = QAbstractSocket::KeepAliveOption;
    t["MulticastTtlOption"] = QAbstractSocket::MulticastTtlOption;
    t["MulticastLoopbackOption"] = QAbstractSocket::MulticastLoopbackOption;
    t["TypeOfServiceOption"] = QAbstractSocket::TypeOfServiceOption;
    t["SendBufferSizeSocketOption"] = QAbstractSocket::SendBufferSizeSocketOption;
    t["ReceiveBufferSizeSocketOption"] = QAbstractSocket::ReceiveBufferSizeSocketOption;

    // enum QAbstractSocket::SocketState
    t["UnconnectedState"] = QAbstractSocket::UnconnectedState;
    t["HostLookupState"] = QAbstractSocket::HostLookupState;
    t["ConnectingState"] = QAbstractSocket::ConnectingState;
    t["ConnectedState"] = QAbstractSocket::ConnectedState;
    t["BoundState"] = QAbstractSocket::BoundState;
    t["ClosingState"] = QAbstractSocket::ClosingState;
    t["ListeningState"] = QAbstractSocket::ListeningState;

    // enum QAbstractSocket::SocketType
    t["TcpSocket"] = QAbstractSocket::TcpSocket;
    t["UdpSocket"] = QAbstractSocket::UdpSocket;
    t["UnknownSocketType"] = QAbstractSocket::UnknownSocketType;

    return 0;
}
