#include "QNetworkAccessManager.hpp"
#include "../convert/callable.hpp"
#include "../convert/const_char_p.hpp"
#include "../thread.hpp"

#include "QNetworkConfiguration.hpp"
#include "QNetworkRequest.hpp"
#include "QNetworkReply.hpp"
#include "QAbstractNetworkCache.hpp"
#include "QNetworkCookieJar.hpp"
#include "QNetworkProxy.hpp"
#include "QNetworkProxyFactory.hpp"
#include "QSslConfiguration.hpp"
#include "../Qt5Core/QStringList.hpp"
#include "../Qt5Core/QIODevice.hpp"
#include "../Qt5Core/QByteArray.hpp"
#include "QHttpMultiPart.hpp"

// http://doc.qt.io/qt-5/qnetworkaccessmanager.html

int QNetworkAccessManager_connectToHost(lua_State* const state)
{
    auto self = lua::get<QNetworkAccessManager*>(state, 1);

    // void     connectToHost(const QString & hostName, quint16 port = 80)
    if (lua_gettop(state) == 2) {
        self->connectToHost(
            lua::get<QString>(state, 2)
        );
    } else {
        self->connectToHost(
            lua::get<QString>(state, 2),
            lua::get<quint16>(state, 3)
        );
    }

    return 1;
}

int QNetworkAccessManager_connectToHostEncrypted(lua_State* const state)
{
    auto self = lua::get<QNetworkAccessManager*>(state, 1);

    // void     connectToHostEncrypted(const QString & hostName, quint16 port = 443, const QSslConfiguration & sslConfiguration = QSslConfiguration::defaultConfiguration())
    switch (lua_gettop(state)) {
    case 2:
        self->connectToHostEncrypted(
            lua::get<QString>(state, 2)
        );
        break;
    case 3:
        self->connectToHostEncrypted(
            lua::get<QString>(state, 2),
            lua::get<quint16>(state, 3)
        );
        break;
    case 4:
        self->connectToHostEncrypted(
            lua::get<QString>(state, 2),
            lua::get<quint16>(state, 3),
            lua::get<const QSslConfiguration&>(state, 4)
        );
        break;
    }

    return 1;
}

int QNetworkAccessManager_post(lua_State* const state)
{
    auto self = lua::get<QNetworkAccessManager*>(state, 1);
    if (lua::is_type<QByteArray>(state, 2)) {
        // QNetworkReply post(const QNetworkRequest & request, const QByteArray & data)
        lua::push(state, self->post(
            lua::get<const QNetworkRequest&>(state, 2),
            lua::get<const QByteArray&>(state, 3)
        ));
    } else if (lua::is_type<QHttpMultiPart>(state, 2)) {
        // QNetworkReply post(const QNetworkRequest & request, QHttpMultiPart * multiPart)
        lua::push(state, self->post(
            lua::get<const QNetworkRequest&>(state, 2),
            lua::get<QHttpMultiPart*>(state, 3)
        ));
    } else {
        // QNetworkReply post(const QNetworkRequest & request, QIODevice * data)
        lua::push(state, self->post(
            lua::get<const QNetworkRequest&>(state, 2),
            lua::get<QIODevice*>(state, 3)
        ));
    }

    return 1;
}

int QNetworkAccessManager_put(lua_State* const state)
{
    auto self = lua::get<QNetworkAccessManager*>(state, 1);
    if (lua::is_type<QByteArray>(state, 2)) {
        // QNetworkReply put(const QNetworkRequest & request, const QByteArray & data)
        lua::push(state, self->put(
            lua::get<const QNetworkRequest&>(state, 2),
            lua::get<const QByteArray&>(state, 3)
        ));
    } else if (lua::is_type<QHttpMultiPart>(state, 2)) {
        // QNetworkReply put(const QNetworkRequest & request, QHttpMultiPart * multiPart)
        lua::push(state, self->put(
            lua::get<const QNetworkRequest&>(state, 2),
            lua::get<QHttpMultiPart*>(state, 3)
        ));
    } else {
        // QNetworkReply put(const QNetworkRequest & request, QIODevice * data)
        lua::push(state, self->put(
            lua::get<const QNetworkRequest&>(state, 2),
            lua::get<QIODevice*>(state, 3)
        ));
    }

    return 1;
}

int QNetworkAccessManager_sendCustomRequest(lua_State* const state)
{
    auto self = lua::get<QNetworkAccessManager*>(state, 1);

    // QNetworkReply *  sendCustomRequest(const QNetworkRequest & request, const QByteArray & verb, QIODevice * data = 0)
    if (lua_gettop(state) == 3) {
        lua::push(state, self->sendCustomRequest(
            lua::get<const QNetworkRequest&>(state, 2),
            lua::get<const QByteArray&>(state, 3)
        ));
    } else {
        lua::push(state, self->sendCustomRequest(
            lua::get<const QNetworkRequest&>(state, 2),
            lua::get<const QByteArray&>(state, 3),
            lua::get<QIODevice*>(state, 4)
        ));
    }

    return 1;
}

namespace lua {

void QNetworkAccessManager_metatable(lua_State* const state, const int pos)
{
    lua::QObject_metatable(state, pos);

    lua::index mt(state, pos);
    mt["activeConfiguration"] = &QNetworkAccessManager::activeConfiguration;
    mt["cache"] = &QNetworkAccessManager::cache;
    mt["clearAccessCache"] = &QNetworkAccessManager::clearAccessCache;
    mt["configuration"] = &QNetworkAccessManager::configuration;
    mt["connectToHost"] = QNetworkAccessManager_connectToHost;
    mt["connectToHostEncrypted"] = QNetworkAccessManager_connectToHostEncrypted;
    mt["cookieJar"] = &QNetworkAccessManager::cookieJar;
    mt["deleteResource"] = &QNetworkAccessManager::deleteResource;
    mt["get"] = &QNetworkAccessManager::get;
    mt["head"] = &QNetworkAccessManager::head;
    mt["networkAccessible"] = &QNetworkAccessManager::networkAccessible;
    mt["post"] = QNetworkAccessManager_post;
    mt["proxy"] = &QNetworkAccessManager::proxy;
    mt["proxyFactory"] = &QNetworkAccessManager::proxyFactory;
    mt["put"] = QNetworkAccessManager_put;
    mt["sendCustomRequest"] = QNetworkAccessManager_sendCustomRequest;
    mt["setCache"] = &QNetworkAccessManager::setCache;
    mt["setConfiguration"] = &QNetworkAccessManager::setConfiguration;
    mt["setCookieJar"] = &QNetworkAccessManager::setCookieJar;
    mt["setNetworkAccessible"] = &QNetworkAccessManager::setNetworkAccessible;
    mt["setProxy"] = &QNetworkAccessManager::setProxy;
    mt["setProxyFactory"] = &QNetworkAccessManager::setProxyFactory;
    mt["supportedSchemes"] = &QNetworkAccessManager::supportedSchemes;
}

} // namespace lua

int QNetworkAccessManager_new(lua_State* const state)
{
    if (lua_gettop(state) == 0) {
        lua::push(state, new QNetworkAccessManager);
    } else {
        lua::push(state, new QNetworkAccessManager(
            lua::get<QObject*>(state, 1)
        ));
    }

    return 1;
}

int luaopen_Qt5Network_QNetworkAccessManager(lua_State* const state)
{
    lua::thread env(state);

    env["QNetworkAccessManager"] = lua::value::table;
    env["QNetworkAccessManager"]["new"] = QNetworkAccessManager_new;
    auto t = env["QNetworkAccessManager"];

    // enum QNetworkAccessManager::NetworkAccessibility
    t["UnknownAccessibility"] = QNetworkAccessManager::UnknownAccessibility;
    t["NotAccessible"] = QNetworkAccessManager::NotAccessible;
    t["Accessible"] = QNetworkAccessManager::Accessible;

    // enum QNetworkAccessManager::Operation
    t["HeadOperation"] = QNetworkAccessManager::HeadOperation;
    t["GetOperation"] = QNetworkAccessManager::GetOperation;
    t["PutOperation"] = QNetworkAccessManager::PutOperation;
    t["PostOperation"] = QNetworkAccessManager::PostOperation;
    t["DeleteOperation"] = QNetworkAccessManager::DeleteOperation;
    t["CustomOperation"] = QNetworkAccessManager::CustomOperation;

    return 0;
}
