#include "QAuthenticator.hpp"
#include "../convert/callable.hpp"
#include "../convert/const_char_p.hpp"
#include "../thread.hpp"

#include "../Qt5Core/QString.hpp"
#include "../Qt5Core/QVariant.hpp"
#include "../Qt5Core/QVariantHash.hpp"

// http://qt-project.org/doc/qt-5/qauthenticator.html

namespace lua {

void QAuthenticator_metatable(lua_State* const state, const int pos)
{
    lua::index mt(state, pos);
    mt["isNull"] = &QAuthenticator::isNull;
    mt["option"] = &QAuthenticator::option;
    mt["options"] = &QAuthenticator::options;
    mt["password"] = &QAuthenticator::password;
    mt["realm"] = &QAuthenticator::realm;
    mt["setOption"] = &QAuthenticator::setOption;
    mt["setPassword"] = &QAuthenticator::setPassword;
    mt["setUser"] = &QAuthenticator::setUser;
    mt["user"] = &QAuthenticator::user;
}

} // namespace lua

int QAuthenticator_new(lua_State* const state)
{
    if (lua_gettop(state) == 0) {
        lua::make<QAuthenticator>(state);
    } else {
        lua::make<QAuthenticator>(state,
            lua::get<const QAuthenticator&>(state, 1)
        );
    }

    return 1;
}

int luaopen_Qt5Network_QAuthenticator(lua_State* const state)
{
    lua::thread env(state);

    env["QAuthenticator"] = lua::value::table;
    env["QAuthenticator"]["new"] = QAuthenticator_new;
    auto t = env["QAuthenticator"];

    return 0;
}
