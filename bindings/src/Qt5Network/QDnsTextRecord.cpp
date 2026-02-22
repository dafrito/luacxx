#include "QDnsTextRecord.hpp"
#include "../convert/callable.hpp"
#include "../convert/const_char_p.hpp"
#include "../thread.hpp"

#include "../Qt5Core/QString.hpp"
#include "../Qt5Core/QList.hpp"
#include "../Qt5Core/QByteArray.hpp"

// http://doc.qt.io/qt-5/qdnstextrecord.html

namespace lua {

void QDnsTextRecord_metatable(lua_State* const state, const int pos)
{
    lua::index mt(state, pos);
    mt["name"] = &QDnsTextRecord::name;
    mt["swap"] = &QDnsTextRecord::swap;
    mt["timeToLive"] = &QDnsTextRecord::timeToLive;
    mt["values"] = &QDnsTextRecord::values;
}

} // namespace lua

int QDnsTextRecord_new(lua_State* const state)
{
    if (lua_gettop(state) == 0) {
        // QDnsTextRecord()
        lua::make<QDnsTextRecord>(state);
    } else {
        // QDnsTextRecord(const QDnsTextRecord & other)
        lua::make<QDnsTextRecord>(state,
            lua::get<const QDnsTextRecord&>(state, 1)
        );
    }

    return 1;
}

int luaopen_Qt5Network_QDnsTextRecord(lua_State* const state)
{
    lua::thread env(state);

    env["QDnsTextRecord"] = lua::value::table;
    env["QDnsTextRecord"]["new"] = QDnsTextRecord_new;
    auto t = env["QDnsTextRecord"];

    return 0;
}
