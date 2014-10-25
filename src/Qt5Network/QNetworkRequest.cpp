#include "QNetworkRequest.hpp"
#include "../convert/callable.hpp"
#include "../thread.hpp"

#include "../Qt5Core/QObject.hpp"
#include "../Qt5Core/QVariant.hpp"
#include "../Qt5Core/QByteArray.hpp"
#include "../Qt5Core/QList.hpp"
#include "QSslConfiguration.hpp"
#include "../Qt5Core/QUrl.hpp"

int QNetworkRequest_attribute(lua_State* const state)
{
    return 0;
}

namespace lua {

void QNetworkRequest_metatable(lua_State* const state, const int pos)
{
    lua::index mt(state, pos);
    mt["attribute"] = QNetworkRequest_attribute;
    mt["hasRawHeader"] = &QNetworkRequest::hasRawHeader;
    mt["header"] = &QNetworkRequest::header;
    mt["originatingObject"] = &QNetworkRequest::originatingObject;
    mt["priority"] = &QNetworkRequest::priority;
    mt["rawHeader"] = &QNetworkRequest::rawHeader;
    mt["rawHeaderList"] = &QNetworkRequest::rawHeaderList;
    mt["setAttribute"] = &QNetworkRequest::setAttribute;
    mt["setHeader"] = &QNetworkRequest::setHeader;
    mt["setOriginatingObject"] = &QNetworkRequest::setOriginatingObject;
    mt["setPriority"] = &QNetworkRequest::setPriority;
    mt["setRawHeader"] = &QNetworkRequest::setRawHeader;
    mt["setSslConfiguration"] = &QNetworkRequest::setSslConfiguration;
    mt["setUrl"] = &QNetworkRequest::setUrl;
    mt["sslConfiguration"] = &QNetworkRequest::sslConfiguration;
    mt["swap"] = &QNetworkRequest::swap;
    mt["url"] = &QNetworkRequest::url;
}

} // namespace lua

int QNetworkRequest_new(lua_State* const state)
{
    // QNetworkRequest(const QUrl & url = QUrl())
    // QNetworkRequest(const QNetworkRequest & other)
    lua::make<QNetworkRequest>(state);
    // TODO Set up constructor

    return 1;
}

int luaopen_luacxx_QNetworkRequest(lua_State* const state)
{
    lua::thread env(state);

    env["QNetworkRequest"] = lua::value::table;
    env["QNetworkRequest"]["new"] = QNetworkRequest_new;
    auto t = env["QNetworkRequest"];

    // enum QNetworkRequest::Attribute
    t["HttpStatusCodeAttribute"] = QNetworkRequest::HttpStatusCodeAttribute;
    t["HttpReasonPhraseAttribute"] = QNetworkRequest::HttpReasonPhraseAttribute;
    t["RedirectionTargetAttribute"] = QNetworkRequest::RedirectionTargetAttribute;
    t["ConnectionEncryptedAttribute"] = QNetworkRequest::ConnectionEncryptedAttribute;
    t["CacheLoadControlAttribute"] = QNetworkRequest::CacheLoadControlAttribute;
    t["CacheSaveControlAttribute"] = QNetworkRequest::CacheSaveControlAttribute;
    t["SourceIsFromCacheAttribute"] = QNetworkRequest::SourceIsFromCacheAttribute;
    t["DoNotBufferUploadDataAttribute"] = QNetworkRequest::DoNotBufferUploadDataAttribute;
    t["HttpPipeliningAllowedAttribute"] = QNetworkRequest::HttpPipeliningAllowedAttribute;
    t["HttpPipeliningWasUsedAttribute"] = QNetworkRequest::HttpPipeliningWasUsedAttribute;
    t["CustomVerbAttribute"] = QNetworkRequest::CustomVerbAttribute;
    t["CookieLoadControlAttribute"] = QNetworkRequest::CookieLoadControlAttribute;
    t["CookieSaveControlAttribute"] = QNetworkRequest::CookieSaveControlAttribute;
    t["AuthenticationReuseAttribute"] = QNetworkRequest::AuthenticationReuseAttribute;
    t["BackgroundRequestAttribute"] = QNetworkRequest::BackgroundRequestAttribute;
    t["SpdyAllowedAttribute"] = QNetworkRequest::SpdyAllowedAttribute;
    t["SpdyWasUsedAttribute"] = QNetworkRequest::SpdyWasUsedAttribute;
    t["User"] = QNetworkRequest::User;
    t["UserMax"] = QNetworkRequest::UserMax;

    // enum QNetworkRequest::CacheLoadControl
    t["AlwaysNetwork"] = QNetworkRequest::AlwaysNetwork;
    t["PreferNetwork"] = QNetworkRequest::PreferNetwork;
    t["PreferCache"] = QNetworkRequest::PreferCache;
    t["AlwaysCache"] = QNetworkRequest::AlwaysCache;

    // enum QNetworkRequest::KnownHeaders
    t["ContentDispositionHeader"] = QNetworkRequest::ContentDispositionHeader;
    t["ContentTypeHeader"] = QNetworkRequest::ContentTypeHeader;
    t["ContentLengthHeader"] = QNetworkRequest::ContentLengthHeader;
    t["LocationHeader"] = QNetworkRequest::LocationHeader;
    t["LastModifiedHeader"] = QNetworkRequest::LastModifiedHeader;
    t["CookieHeader"] = QNetworkRequest::CookieHeader;
    t["SetCookieHeader"] = QNetworkRequest::SetCookieHeader;
    t["UserAgentHeader"] = QNetworkRequest::UserAgentHeader;
    t["ServerHeader"] = QNetworkRequest::ServerHeader;

    // enum QNetworkRequest::LoadControl
    t["Automatic"] = QNetworkRequest::Automatic;
    t["Manual"] = QNetworkRequest::Manual;

    // enum QNetworkRequest::Priority
    t["HighPriority"] = QNetworkRequest::HighPriority;
    t["NormalPriority"] = QNetworkRequest::NormalPriority;
    t["LowPriority"] = QNetworkRequest::LowPriority;

    return 0;
}
