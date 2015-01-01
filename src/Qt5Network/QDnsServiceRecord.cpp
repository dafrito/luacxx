#include "QDnsServiceRecord.hpp"
#include "../convert/callable.hpp"
#include "../convert/const_char_p.hpp"
#include "../thread.hpp"

#include "../Qt5Core/QString.hpp"

// http://doc.qt.io/qt-5/qdnsservicerecord.html

namespace lua {

void QDnsServiceRecord_metatable(lua_State* const state, const int pos)
{
    lua::index mt(state, pos);
    mt["name"] = &QDnsServiceRecord::name;
    mt["port"] = &QDnsServiceRecord::port;
    mt["priority"] = &QDnsServiceRecord::priority;
    mt["swap"] = &QDnsServiceRecord::swap;
    mt["target"] = &QDnsServiceRecord::target;
    mt["timeToLive"] = &QDnsServiceRecord::timeToLive;
    mt["weight"] = &QDnsServiceRecord::weight;
}

} // namespace lua

int QDnsServiceRecord_new(lua_State* const state)
{
    if (lua_gettop(state) == 0) {
        lua::make<QDnsServiceRecord>(state);
    } else {
        lua::make<QDnsServiceRecord>(state,
            lua::get<const QDnsServiceRecord&>(state, 1)
        );
    }

    return 1;
}

int luaopen_Qt5Network_QDnsServiceRecord(lua_State* const state)
{
    lua::thread env(state);

    env["QDnsServiceRecord"] = lua::value::table;
    env["QDnsServiceRecord"]["new"] = QDnsServiceRecord_new;
    auto t = env["QDnsServiceRecord"];

    return 0;
}
