#include "QTcpSocket.hpp"
#include "../thread.hpp"
#include "QAbstractSocket.hpp"

void lua::QTcpSocket_metatable(lua_State* const state, const int pos)
{
    lua::QAbstractSocket_metatable(state, pos);
}

int QTcpSocket_new(lua_State* const state)
{
    lua::make<QTcpSocket>(state);
    return 1;
}

int luaopen_luacxx_QTcpSocket(lua_State* const state)
{
    lua::thread env(state);

    env["QTcpSocket"] = lua::value::table;
    env["QTcpSocket"]["new"] = QTcpSocket_new;
    auto t = env["QTcpSocket"];

    return 0;
}
