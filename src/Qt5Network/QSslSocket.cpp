#include "QSslSocket.hpp"
#include "../thread.hpp"

#include "../Qt5Core/QList.hpp"
#include "QTcpSocket.hpp"
#include "QSslCertificate.hpp"
#include "QSslError.hpp"
#include "QSslKey.hpp"
#include "QSslCipher.hpp"
#include "QSslConfiguration.hpp"
#include "QSsl.hpp"

int QSslSocket_addCaCertificates(lua_State* const state)
{
    return 0;
}
int QSslSocket_connectToHostEncrypted(lua_State* const state)
{
    return 0;
}
int QSslSocket_setCiphers(lua_State* const state)
{
    return 0;
}
int QSslSocket_setLocalCertificate(lua_State* const state)
{
    return 0;
}
int QSslSocket_setPrivateKey(lua_State* const state)
{
    return 0;
}
int QSslSocket_waitForEncrypted(lua_State* const state)
{
    return 0;
}

int QSslSocket_ignoreSslErrors(lua_State* const state)
{
    return 0;
}
int QSslSocket_sslErrors(lua_State* const state)
{
    return 0;
}

void lua::QSslSocket_metatable(lua_State* const state, const int pos)
{
    lua::QTcpSocket_metatable(state, pos);

    lua::index mt(state, pos);
    mt["abort"] = &QSslSocket::abort;
    mt["addCaCertificate"] = &QSslSocket::addCaCertificate;
    mt["addCaCertificates"] = QSslSocket_addCaCertificates;
    mt["caCertificates"] = &QSslSocket::caCertificates;
    mt["ciphers"] = &QSslSocket::ciphers;
    mt["connectToHostEncrypted"] = QSslSocket_connectToHostEncrypted;
    mt["encryptedBytesAvailable"] = &QSslSocket::encryptedBytesAvailable;
    mt["encryptedBytesToWrite"] = &QSslSocket::encryptedBytesToWrite;
    mt["flush"] = &QSslSocket::flush;
    mt["ignoreSslErrors"] = QSslSocket_ignoreSslErrors;
    mt["isEncrypted"] = &QSslSocket::isEncrypted;
    mt["localCertificate"] = &QSslSocket::localCertificate;
    mt["localCertificateChain"] = &QSslSocket::localCertificateChain;
    mt["mode"] = &QSslSocket::mode;
    mt["peerCertificate"] = &QSslSocket::peerCertificate;
    mt["peerCertificateChain"] = &QSslSocket::peerCertificateChain;
    mt["peerVerifyDepth"] = &QSslSocket::peerVerifyDepth;
    mt["peerVerifyMode"] = &QSslSocket::peerVerifyMode;
    mt["peerVerifyName"] = &QSslSocket::peerVerifyName;
    mt["privateKey"] = &QSslSocket::privateKey;
    mt["protocol"] = &QSslSocket::protocol;
    mt["sessionCipher"] = &QSslSocket::sessionCipher;
    mt["setCaCertificates"] = &QSslSocket::setCaCertificates;
    mt["setCiphers"] = QSslSocket_setCiphers;
    mt["setLocalCertificate"] = QSslSocket_setLocalCertificate;
    mt["setPeerVerifyDepth"] = &QSslSocket::setPeerVerifyDepth;
    mt["setPeerVerifyMode"] = &QSslSocket::setPeerVerifyMode;
    mt["setPeerVerifyName"] = &QSslSocket::setPeerVerifyName;
    mt["setPrivateKey"] = QSslSocket_setPrivateKey;
    mt["setProtocol"] = &QSslSocket::setProtocol;
    mt["setSslConfiguration"] = &QSslSocket::setSslConfiguration;
    mt["sslConfiguration"] = &QSslSocket::sslConfiguration;
    mt["sslErrors"] = QSslSocket_sslErrors;
    mt["waitForEncrypted"] = QSslSocket_waitForEncrypted;
}

int QSslSocket_new(lua_State* const state)
{
    // QSslSocket(QObject * parent = 0)
    lua::make<QSslSocket>(state);

    return 1;
}

int QSslSocket_addDefaultCaCertificates(lua_State* const state)
{
    return 0;
}

int luaopen_Qt5Network_QSslSocket(lua_State* const state)
{
    lua::thread env(state);

    env["QSslSocket"] = lua::value::table;
    env["QSslSocket"]["new"] = QSslSocket_new;
    auto t = env["QSslSocket"];

    // enum QSslSocket::PeerVerifyMode
    t["VerifyNone"] = QSslSocket::VerifyNone;
    t["QueryPeer"] = QSslSocket::QueryPeer;
    t["VerifyPeer"] = QSslSocket::VerifyPeer;
    t["AutoVerifyPeer"] = QSslSocket::AutoVerifyPeer;

    // enum QSslSocket::SslMode
    t["UnencryptedMode"] = QSslSocket::UnencryptedMode;
    t["SslClientMode"] = QSslSocket::SslClientMode;
    t["SslServerMode"] = QSslSocket::SslServerMode;

     t["addDefaultCaCertificate"] = &QSslSocket::addDefaultCaCertificate;
     t["addDefaultCaCertificates"] = QSslSocket_addDefaultCaCertificates;
     t["defaultCaCertificates"] = &QSslSocket::defaultCaCertificates;
     t["defaultCiphers"] = &QSslSocket::defaultCiphers;
     t["setDefaultCaCertificates"] = &QSslSocket::setDefaultCaCertificates;
     t["setDefaultCiphers"] = &QSslSocket::setDefaultCiphers;
     t["sslLibraryVersionNumber"] = &QSslSocket::sslLibraryVersionNumber;
     t["sslLibraryVersionString"] = &QSslSocket::sslLibraryVersionString;
     t["supportedCiphers"] = &QSslSocket::supportedCiphers;
     t["supportsSsl"] = &QSslSocket::supportsSsl;
     t["systemCaCertificates"] = &QSslSocket::systemCaCertificates;

    return 0;
}
