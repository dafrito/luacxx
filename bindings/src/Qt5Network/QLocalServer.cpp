#include "QLocalServer.hpp"
#include "../convert/callable.hpp"
#include "../convert/const_char_p.hpp"
#include "../thread.hpp"

#include "../Qt5Core/QString.hpp"
#include "QLocalSocket.hpp"
#include "QAbstractSocket.hpp"
#include "../Qt5Core/QFlags.hpp"

// http://qt-project.org/doc/qt-5/qlocalserver.html#details

int QLocalServer_listen(lua_State* const state)
{
    auto self = lua::get<QLocalServer*>(state, 1);

    // bool listen(const QString & name)
    // bool listen(qintptr socketDescriptor)
    if (lua_type(state, 2) == LUA_TNUMBER) {
        lua::push(state, self->listen(
            lua::get<qintptr>(state, 2)
        ));
    } else {
        lua::push(state, self->listen(
            lua::get<QString>(state, 2)
        ));
    }

    return 1;
}

int QLocalServer_waitForNewConnection(lua_State* const state)
{
    auto self = lua::get<QLocalServer*>(state, 1);

    // bool waitForNewConnection(int msec = 0, bool * timedOut = 0)
    switch (lua_gettop(state)) {
    case 1:
        lua::push(state, self->waitForNewConnection());
        break;
    case 2:
    {
        bool timedOut;
        lua::push(state, self->waitForNewConnection(
            lua::get<int>(state, 2),
            &timedOut
        ));
        lua::push(state, timedOut);
        return 2;
    }
    case 3:
    default:
        lua::push(state, self->waitForNewConnection(
            lua::get<int>(state, 2),
            lua::get<bool*>(state, 3)
        ));
        break;
    }

    return 1;
}

namespace lua {

void QLocalServer_metatable(lua_State* const state, const int pos)
{
    lua::QObject_metatable(state, pos);

    lua::index mt(state, pos);
    mt["close"] = &QLocalServer::close;
    mt["errorString"] = &QLocalServer::errorString;
    mt["fullServerName"] = &QLocalServer::fullServerName;
    mt["hasPendingConnections"] = &QLocalServer::hasPendingConnections;
    mt["isListening"] = &QLocalServer::isListening;
    mt["listen"] = QLocalServer_listen;
    mt["maxPendingConnections"] = &QLocalServer::maxPendingConnections;
    mt["nextPendingConnection"] = &QLocalServer::nextPendingConnection;
    mt["serverError"] = &QLocalServer::serverError;
    mt["serverName"] = &QLocalServer::serverName;
    mt["setMaxPendingConnections"] = &QLocalServer::setMaxPendingConnections;
    mt["setSocketOptions"] = &QLocalServer::setSocketOptions;
    mt["socketOptions"] = &QLocalServer::socketOptions;
    mt["waitForNewConnection"] = QLocalServer_waitForNewConnection;
}

} // namespace lua

int QLocalServer_new(lua_State* const state)
{
    if (lua_gettop(state) == 0) {
        lua::push(state, new QLocalServer);
    } else {
        lua::push(state, new QLocalServer(
            lua::get<QObject*>(state, 1)
        ));
    }

    return 1;
}

int luaopen_Qt5Network_QLocalServer(lua_State* const state)
{
    lua::thread env(state);

    env["QLocalServer"] = lua::value::table;
    env["QLocalServer"]["new"] = QLocalServer_new;
    auto t = env["QLocalServer"];

    // enum QLocalServer::SocketOption
    t["SocketOptions"] = lua::QFlags_new<QLocalServer::SocketOption>;
    t["NoOptions"] = QLocalServer::NoOptions;
    t["UserAccessOption"] = QLocalServer::UserAccessOption;
    t["GroupAccessOption"] = QLocalServer::GroupAccessOption;
    t["OtherAccessOption"] = QLocalServer::OtherAccessOption;
    t["WorldAccessOption"] = QLocalServer::WorldAccessOption;

    return 0;
}
