#include "QNetworkInterface.hpp"
#include "../thread.hpp"

#include "../Qt5Core/QList.hpp"
#include "QNetworkAddressEntry.hpp"

bool operator==(const QNetworkInterface& first, const QNetworkInterface& second)
{
    return first.index() == second.index();
}

void lua::QNetworkInterface_metatable(lua_State* const state, const int pos)
{
    lua::index mt(state, pos);
    mt["addressEntries"] = &QNetworkInterface::addressEntries;
    mt["flags"] = &QNetworkInterface::flags;
    mt["hardwareAddress"] = &QNetworkInterface::hardwareAddress;
    mt["humanReadableName"] = &QNetworkInterface::humanReadableName;
    mt["index"] = &QNetworkInterface::index;
    mt["isValid"] = &QNetworkInterface::isValid;
    mt["name"] = &QNetworkInterface::name;
    mt["swap"] = &QNetworkInterface::swap;
}

int QNetworkInterface_new(lua_State* const state)
{
    if (lua::size(state) == 1) {
        // QNetworkInterface()
        lua::make<QNetworkInterface>(state);
    } else {
        // QNetworkInterface(const QNetworkInterface & other)
        lua::make<QNetworkInterface>(state, lua::get<const QNetworkInterface&>(state, 2));
    }

    return 1;
}

int luaopen_luacxx_QNetworkInterface(lua_State* const state)
{
    lua::thread env(state);

    env["QNetworkInterface"] = lua::value::table;
    env["QNetworkInterface"]["new"] = QNetworkInterface_new;
    auto t = env["QNetworkInterface"];

    t["allAddresses"] = &QNetworkInterface::allAddresses;
    t["allInterfaces"] = &QNetworkInterface::allInterfaces;
    t["interfaceFromIndex"] = &QNetworkInterface::interfaceFromIndex;
    t["interfaceFromName"] = &QNetworkInterface::interfaceFromName;

    // enum QNetworkInterface::InterfaceFlag
    t["IsUp"] = QNetworkInterface::IsUp;
    t["IsRunning"] = QNetworkInterface::IsRunning;
    t["CanBroadcast"] = QNetworkInterface::CanBroadcast;
    t["IsLoopBack"] = QNetworkInterface::IsLoopBack;
    t["IsPointToPoint"] = QNetworkInterface::IsPointToPoint;
    t["CanMulticast"] = QNetworkInterface::CanMulticast;

    return 0;
}
