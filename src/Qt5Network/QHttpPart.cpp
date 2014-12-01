#include "QHttpPart.hpp"
#include "../convert/callable.hpp"
#include "../convert/const_char_p.hpp"
#include "../thread.hpp"

#include "../Qt5Core/QByteArray.hpp"
#include "../Qt5Core/QIODevice.hpp"
#include "../Qt5Core/QVariant.hpp"
#include "QNetworkRequest.hpp"

// http://qt-project.org/doc/qt-5/qhttppart.html

namespace lua {

void QHttpPart_metatable(lua_State* const state, const int pos)
{
    lua::index mt(state, pos);
    mt["setBody"] = &QHttpPart::setBody;
    mt["setBodyDevice"] = &QHttpPart::setBodyDevice;
    mt["setHeader"] = &QHttpPart::setHeader;
    mt["setRawHeader"] = &QHttpPart::setRawHeader;
    mt["swap"] = &QHttpPart::swap;
}

} // namespace lua

int QHttpPart_new(lua_State* const state)
{
    if (lua_gettop(state) == 0) {
        // QHttpPart()
        lua::make<QHttpPart>(state);
    } else {
        // QHttpPart(const QHttpPart & other)
        lua::make<QHttpPart>(state,
            lua::get<const QHttpPart&>(state, 1)
        );
    }

    return 1;
}

int luaopen_Qt5Network_QHttpPart(lua_State* const state)
{
    lua::thread env(state);

    env["QHttpPart"] = lua::value::table;
    env["QHttpPart"]["new"] = QHttpPart_new;
    auto t = env["QHttpPart"];

    return 0;
}
