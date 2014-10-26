#include "QHostAddress.hpp"
#include "../thread.hpp"
#include "QAbstractSocket.hpp"

#include <QHostAddress>

int QHostAddress_isInSubnet(lua_State* const state)
{
    return 0;
}

int QHostAddress_setAddress(lua_State* const state)
{
    return 0;
}

void lua::Q_IPV6ADDR_metatable(lua_State* const state, const int pos)
{

}

void lua::QHostAddress_metatable(lua_State* const state, const int pos)
{
    lua::index mt(state, pos);
    mt["clear"] = &QHostAddress::clear;
    mt["isInSubnet"] = QHostAddress_isInSubnet;
    mt["setAddress"] = QHostAddress_setAddress;
    mt["isLoopback"] = &QHostAddress::isLoopback;
    mt["isNull"] = &QHostAddress::isNull;
    mt["protocol"] = &QHostAddress::protocol;
    mt["scopeId"] = &QHostAddress::scopeId;
    mt["setAddress"] = QHostAddress_setAddress;
    mt["setScopeId"] = &QHostAddress::setScopeId;
    mt["toIPv4Address"] = &QHostAddress::toIPv4Address;
    mt["toIPv6Address"] = &QHostAddress::toIPv6Address;
    mt["toString"] = &QHostAddress::toString;
}

int QHostAddress_new(lua_State* const state)
{
    // QHostAddress()
    // QHostAddress(quint32 ip4Addr)
    // QHostAddress(quint8 * ip6Addr)
    // QHostAddress(const Q_IPV6ADDR & ip6Addr)
    // QHostAddress(const sockaddr * sockaddr)
    // QHostAddress(const QString & address)
    // QHostAddress(const QHostAddress & address)
    // QHostAddress(SpecialAddress address)
    lua::make<QHostAddress>(state);

    return 1;
}

int luaopen_Qt5Network_QHostAddress(lua_State* const state)
{
    lua::thread env(state);

    env["QHostAddress"] = lua::value::table;
    env["QHostAddress"]["new"] = QHostAddress_new;
    auto t = env["QHostAddress"];

    // enum QHostAddress::SpecialAddress
    t["Null"] = QHostAddress::Null;
    t["LocalHost"] = QHostAddress::LocalHost;
    t["LocalHostIPv6"] = QHostAddress::LocalHostIPv6;
    t["Broadcast"] = QHostAddress::Broadcast;
    t["AnyIPv4"] = QHostAddress::AnyIPv4;
    t["AnyIPv6"] = QHostAddress::AnyIPv6;
    t["Any"] = QHostAddress::Any;

    return 0;
}
