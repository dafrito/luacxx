#include "QDnsDomainNameRecord.hpp"
#include "../convert/callable.hpp"
#include "../convert/const_char_p.hpp"
#include "../thread.hpp"

#include "../Qt5Core/QString.hpp"

// http://doc.qt.io/qt-5/qdnsdomainnamerecord.html

namespace lua {

void QDnsDomainNameRecord_metatable(lua_State* const state, const int pos)
{
    lua::index mt(state, pos);
    mt["name"] = &QDnsDomainNameRecord::name;
    mt["swap"] = &QDnsDomainNameRecord::swap;
    mt["timeToLive"] = &QDnsDomainNameRecord::timeToLive;
    mt["value"] = &QDnsDomainNameRecord::value;
}

} // namespace lua

int QDnsDomainNameRecord_new(lua_State* const state)
{
    if (lua_gettop(state) == 0) {
        // QDnsDomainNameRecord()
        lua::make<QDnsDomainNameRecord>(state);
    } else {
        // QDnsDomainNameRecord(const QDnsDomainNameRecord & other)
        lua::make<QDnsDomainNameRecord>(state,
            lua::get<const QDnsDomainNameRecord&>(state, 1)
        );
    }
    return 1;
}

int luaopen_Qt5Network_QDnsDomainNameRecord(lua_State* const state)
{
    lua::thread env(state);

    env["QDnsDomainNameRecord"] = lua::value::table;
    env["QDnsDomainNameRecord"]["new"] = QDnsDomainNameRecord_new;
    auto t = env["QDnsDomainNameRecord"];

    return 0;
}
