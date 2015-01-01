#include "QDnsHostAddressRecord.hpp"
#include "../convert/callable.hpp"
#include "../convert/const_char_p.hpp"
#include "../thread.hpp"

#include "QHostAddress.hpp"
#include "../Qt5Core/QString.hpp"

// http://doc.qt.io/qt-5/qdnshostaddressrecord.html

namespace lua {

void QDnsHostAddressRecord_metatable(lua_State* const state, const int pos)
{
    lua::index mt(state, pos);
    mt["name"] = &QDnsHostAddressRecord::name;
    mt["swap"] = &QDnsHostAddressRecord::swap;
    mt["timeToLive"] = &QDnsHostAddressRecord::timeToLive;
    mt["value"] = &QDnsHostAddressRecord::value;
}

} // namespace lua

int QDnsHostAddressRecord_new(lua_State* const state)
{
    if (lua_gettop(state) == 0) {
        // QDnsHostAddressRecord()
        lua::make<QDnsHostAddressRecord>(state);
    } else {
        // QDnsHostAddressRecord(const QDnsHostAddressRecord & other)
        lua::make<QDnsHostAddressRecord>(state,
            lua::get<const QDnsHostAddressRecord&>(state, 1)
        );
    }

    return 1;
}

int luaopen_Qt5Network_QDnsHostAddressRecord(lua_State* const state)
{
    lua::thread env(state);

    env["QDnsHostAddressRecord"] = lua::value::table;
    env["QDnsHostAddressRecord"]["new"] = QDnsHostAddressRecord_new;
    auto t = env["QDnsHostAddressRecord"];

    return 0;
}
