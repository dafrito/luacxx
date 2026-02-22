#include "QNetworkCookie.hpp"
#include "../convert/callable.hpp"
#include "../convert/const_char_p.hpp"
#include "../thread.hpp"

#include "../Qt5Core/QByteArray.hpp"
#include "../Qt5Core/QDateTime.hpp"
#include "../Qt5Core/QUrl.hpp"
#include "../Qt5Core/QString.hpp"
#include "../Qt5Core/QList.hpp"

// http://doc.qt.io/qt-5/qnetworkcookie.html

int QNetworkCookie_toRawForm(lua_State* const state)
{
    auto self = lua::get<QNetworkCookie*>(state, 1);

    if (lua_gettop(state) == 1) {
        lua::push(state, self->toRawForm());
    } else {
        lua::push(state, self->toRawForm(
            lua::get<QNetworkCookie::RawForm>(state, 2)
        ));
    }

    return 1;
}

namespace lua {

void QNetworkCookie_metatable(lua_State* const state, const int pos)
{
    lua::index mt(state, pos);
    mt["domain"] = &QNetworkCookie::domain;
    mt["expirationDate"] = &QNetworkCookie::expirationDate;
    mt["hasSameIdentifier"] = &QNetworkCookie::hasSameIdentifier;
    mt["isHttpOnly"] = &QNetworkCookie::isHttpOnly;
    mt["isSecure"] = &QNetworkCookie::isSecure;
    mt["isSessionCookie"] = &QNetworkCookie::isSessionCookie;
    mt["name"] = &QNetworkCookie::name;
    mt["normalize"] = &QNetworkCookie::normalize;
    mt["path"] = &QNetworkCookie::path;
    mt["setDomain"] = &QNetworkCookie::setDomain;
    mt["setExpirationDate"] = &QNetworkCookie::setExpirationDate;
    mt["setHttpOnly"] = &QNetworkCookie::setHttpOnly;
    mt["setName"] = &QNetworkCookie::setName;
    mt["setPath"] = &QNetworkCookie::setPath;
    mt["setSecure"] = &QNetworkCookie::setSecure;
    mt["setValue"] = &QNetworkCookie::setValue;
    mt["swap"] = &QNetworkCookie::swap;
    mt["toRawForm"] = QNetworkCookie_toRawForm;
    mt["value"] = &QNetworkCookie::value;
}

} // namespace lua

int QNetworkCookie_new(lua_State* const state)
{
    // QNetworkCookie(const QByteArray & name = QByteArray(), const QByteArray & value = QByteArray())
    // QNetworkCookie(const QNetworkCookie & other)
    switch (lua_gettop(state)) {
    case 0:
        lua::make<QNetworkCookie>(state);
        break;
    case 1:
        if (lua::is_type<QNetworkCookie>(state, 1)) {
            lua::make<QNetworkCookie>(state,
                lua::get<const QNetworkCookie&>(state, 1)
            );
        } else {
            lua::make<QNetworkCookie>(state,
                lua::get<const QByteArray&>(state, 1)
            );
        }
        break;
    case 2:
    default:
        lua::make<QNetworkCookie>(state,
            lua::get<const QByteArray&>(state, 1),
            lua::get<const QByteArray&>(state, 2)
        );
        break;
    }

    return 1;
}

int luaopen_Qt5Network_QNetworkCookie(lua_State* const state)
{
    lua::thread env(state);

    env["QNetworkCookie"] = lua::value::table;
    env["QNetworkCookie"]["new"] = QNetworkCookie_new;
    auto t = env["QNetworkCookie"];

    t["parseCookies"] = QNetworkCookie::parseCookies;

    // enum QNetworkCookie::RawForm
    t["NameAndValueOnly"] = QNetworkCookie::NameAndValueOnly;
    t["Full"] = QNetworkCookie::Full;

    return 0;
}
