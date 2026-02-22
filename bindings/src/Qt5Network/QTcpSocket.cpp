#include "QTcpSocket.hpp"
#include "../thread.hpp"
#include "QAbstractSocket.hpp"
#include "../Qt5Core/QObject.hpp"

void lua::QTcpSocket_metatable(lua_State* const state, const int pos)
{
    lua::QAbstractSocket_metatable(state, pos);
}

int QTcpSocket_new(lua_State* const state)
{
    if (lua_gettop(state) == 1) {
        lua::push(state, new QTcpSocket(lua::get<QObject*>(state, 1)));
    } else {
        lua::push(state, new QTcpSocket);
    }
    return 1;
}

int luaopen_Qt5Network_QTcpSocket(lua_State* const state)
{
    lua::thread env(state);

    env["QTcpSocket"] = lua::value::table;
    env["QTcpSocket"]["new"] = QTcpSocket_new;
    auto t = env["QTcpSocket"];

    return 0;
}
