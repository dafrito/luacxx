#include "QNetworkProxy.hpp"
#include "../convert/callable.hpp"
#include "../thread.hpp"

#include "../Qt5Core/QByteArray.hpp"
#include "../Qt5Core/QString.hpp"
#include "../Qt5Core/QList.hpp"
#include "../Qt5Core/QVariant.hpp"
#include "../Qt5Core/QFlags.hpp"
#include "QNetworkRequest.hpp"

namespace lua {

void QNetworkProxy_metatable(lua_State* const state, const int pos)
{
    lua::index mt(state, pos);
    mt["capabilities"] = &QNetworkProxy::capabilities;
    mt["hasRawHeader"] = &QNetworkProxy::hasRawHeader;
    mt["header"] = &QNetworkProxy::header;
    mt["hostName"] = &QNetworkProxy::hostName;
    mt["isCachingProxy"] = &QNetworkProxy::isCachingProxy;
    mt["isTransparentProxy"] = &QNetworkProxy::isTransparentProxy;
    mt["password"] = &QNetworkProxy::password;
    mt["port"] = &QNetworkProxy::port;
    mt["rawHeader"] = &QNetworkProxy::rawHeader;
    mt["rawHeaderList"] = &QNetworkProxy::rawHeaderList;
    mt["setCapabilities"] = &QNetworkProxy::setCapabilities;
    mt["setHeader"] = &QNetworkProxy::setHeader;
    mt["setHostName"] = &QNetworkProxy::setHostName;
    mt["setPassword"] = &QNetworkProxy::setPassword;
    mt["setPort"] = &QNetworkProxy::setPort;
    mt["setRawHeader"] = &QNetworkProxy::setRawHeader;
    mt["setType"] = &QNetworkProxy::setType;
    mt["setUser"] = &QNetworkProxy::setUser;
    mt["swap"] = &QNetworkProxy::swap;
    mt["type"] = &QNetworkProxy::type;
    mt["user"] = &QNetworkProxy::user;
}

} // namespace lua

int QNetworkProxy_new(lua_State* const state)
{
    // QNetworkProxy()
    // QNetworkProxy(ProxyType type, const QString & hostName = QString(), quint16 port = 0, const QString & user = QString(), const QString & password = QString())
    // QNetworkProxy(const QNetworkProxy & other)
    lua::make<QNetworkProxy>(state);
    // TODO Set up constructor

    return 1;
}

int luaopen_Qt5Network_QNetworkProxy(lua_State* const state)
{
    lua::thread env(state);

    env["QNetworkProxy"] = lua::value::table;
    env["QNetworkProxy"]["new"] = QNetworkProxy_new;
    auto t = env["QNetworkProxy"];

    // enum QNetworkProxy::Capability
    t["Capabilities"] = lua::QFlags_new<QNetworkProxy::Capabilities>;
    t["TunnelingCapability"] = QNetworkProxy::TunnelingCapability;
    t["ListeningCapability"] = QNetworkProxy::ListeningCapability;
    t["UdpTunnelingCapability"] = QNetworkProxy::UdpTunnelingCapability;
    t["CachingCapability"] = QNetworkProxy::CachingCapability;
    t["HostNameLookupCapability"] = QNetworkProxy::HostNameLookupCapability;

    // enum QNetworkProxy::ProxyType
    t["NoProxy"] = QNetworkProxy::NoProxy;
    t["DefaultProxy"] = QNetworkProxy::DefaultProxy;
    t["Socks5Proxy"] = QNetworkProxy::Socks5Proxy;
    t["HttpProxy"] = QNetworkProxy::HttpProxy;
    t["HttpCachingProxy"] = QNetworkProxy::HttpCachingProxy;
    t["FtpCachingProxy"] = QNetworkProxy::FtpCachingProxy;

    return 0;
}
