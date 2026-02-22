#include "QNetworkAddressEntry.hpp"
#include "../thread.hpp"

#include "QHostAddress.hpp"

void lua::QNetworkAddressEntry_metatable(lua_State* const state, const int pos)
{
    lua::index mt(state, pos);
    mt["broadcast"] = &QNetworkAddressEntry::broadcast;
    mt["ip"] = &QNetworkAddressEntry::ip;
    mt["netmask"] = &QNetworkAddressEntry::netmask;
    mt["prefixLength"] = &QNetworkAddressEntry::prefixLength;
    mt["setBroadcast"] = &QNetworkAddressEntry::setBroadcast;
    mt["setIp"] = &QNetworkAddressEntry::setIp;
    mt["setNetmask"] = &QNetworkAddressEntry::setNetmask;
    mt["setPrefixLength"] = &QNetworkAddressEntry::setPrefixLength;
    mt["swap"] = &QNetworkAddressEntry::swap;
}

int QNetworkAddressEntry_new(lua_State* const state)
{
    if (lua::size(state) == 1) {
        // QNetworkAddressEntry()
        lua::make<QNetworkAddressEntry>(state);
    } else {
        // QNetworkAddressEntry(const QNetworkAddressEntry & other)
        lua::make<QNetworkAddressEntry>(state, lua::get<const QNetworkAddressEntry&>(state, 2));
    }
    return 1;
}

int luaopen_Qt5Network_QNetworkAddressEntry(lua_State* const state)
{
    lua::thread env(state);

    env["QNetworkAddressEntry"] = lua::value::table;
    env["QNetworkAddressEntry"]["new"] = QNetworkAddressEntry_new;
    auto t = env["QNetworkAddressEntry"];

    return 0;
}
