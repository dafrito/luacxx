#include "QHostInfo.hpp"
#include "../convert/callable.hpp"
#include "../convert/const_char_p.hpp"
#include "../thread.hpp"

#include "QHostAddress.hpp"
#include "../Qt5Core/QString.hpp"
#include "../Qt5Core/QList.hpp"

// http://qt-project.org/doc/qt-5/qhostinfo.html

namespace lua {

void QHostInfo_metatable(lua_State* const state, const int pos)
{
    lua::index mt(state, pos);
    mt["addresses"] = &QHostInfo::addresses;
    mt["error"] = &QHostInfo::error;
    mt["errorString"] = &QHostInfo::errorString;
    mt["hostName"] = &QHostInfo::hostName;
    mt["lookupId"] = &QHostInfo::lookupId;
    mt["setAddresses"] = &QHostInfo::setAddresses;
    mt["setError"] = &QHostInfo::setError;
    mt["setErrorString"] = &QHostInfo::setErrorString;
    mt["setHostName"] = &QHostInfo::setHostName;
    mt["setLookupId"] = &QHostInfo::setLookupId;
}

} // namespace lua

int QHostInfo_new(lua_State* const state)
{
    // QHostInfo(int id = -1)
    // QHostInfo(const QHostInfo & other)
    if (lua_gettop(state) == 0) {
        lua::make<QHostInfo>(state);
    } else if (lua::is_type<QHostInfo>(state, 1)) {
        lua::make<QHostInfo>(state, lua::get<const QHostInfo&>(state, 1));
    } else {
        lua::make<QHostInfo>(state, lua::get<int>(state, 1));
    }

    return 1;
}

int luaopen_Qt5Network_QHostInfo(lua_State* const state)
{
    lua::thread env(state);

    env["QHostInfo"] = lua::value::table;
    env["QHostInfo"]["new"] = QHostInfo_new;
    auto t = env["QHostInfo"];

    // enum QHostInfo::HostInfoError
    t["NoError"] = QHostInfo::NoError;
    t["HostNotFound"] = QHostInfo::HostNotFound;
    t["UnknownError"] = QHostInfo::UnknownError;

    return 0;
}
