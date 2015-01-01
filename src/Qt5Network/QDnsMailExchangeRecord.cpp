#include "QDnsMailExchangeRecord.hpp"
#include "../convert/callable.hpp"
#include "../convert/const_char_p.hpp"
#include "../thread.hpp"

#include "../Qt5Core/QString.hpp"

namespace lua {

void QDnsMailExchangeRecord_metatable(lua_State* const state, const int pos)
{
    lua::index mt(state, pos);
    mt["exchange"] = &QDnsMailExchangeRecord::exchange;
    mt["name"] = &QDnsMailExchangeRecord::name;
    mt["preference"] = &QDnsMailExchangeRecord::preference;
    mt["swap"] = &QDnsMailExchangeRecord::swap;
    mt["timeToLive"] = &QDnsMailExchangeRecord::timeToLive;
}

} // namespace lua

int QDnsMailExchangeRecord_new(lua_State* const state)
{
    if (lua_gettop(state) == 0) {
        lua::make<QDnsMailExchangeRecord>(state);
    } else {
        lua::make<QDnsMailExchangeRecord>(state,
            lua::get<const QDnsMailExchangeRecord&>(state, 1)
        );
    }

    return 1;
}

int luaopen_Qt5Network_QDnsMailExchangeRecord(lua_State* const state)
{
    lua::thread env(state);

    env["QDnsMailExchangeRecord"] = lua::value::table;
    env["QDnsMailExchangeRecord"]["new"] = QDnsMailExchangeRecord_new;
    auto t = env["QDnsMailExchangeRecord"];

    return 0;
}
