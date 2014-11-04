#include "QFileSystemWatcher.hpp"
#include "../convert/callable.hpp"
#include "../thread.hpp"

#include "QObject.hpp"
#include "QStringList.hpp"
#include "QString.hpp"

namespace lua {

void QFileSystemWatcher_metatable(lua_State* const state, const int pos)
{
    lua::QObject_metatable(state, pos);

    lua::index mt(state, pos);
    mt["addPath"] = &QFileSystemWatcher::addPath;
    mt["addPaths"] = &QFileSystemWatcher::addPaths;
    mt["directories"] = &QFileSystemWatcher::directories;
    mt["files"] = &QFileSystemWatcher::files;
    mt["removePath"] = &QFileSystemWatcher::removePath;
    mt["removePaths"] = &QFileSystemWatcher::removePaths;
}

} // namespace lua

int QFileSystemWatcher_new(lua_State* const state)
{
    switch (lua_gettop(state)) {
    case 0:
        lua::push(state, new QFileSystemWatcher);
        break;
    case 1:
        if (lua::is_type<QStringList>(state, 1)) {
            lua::push(state, new QFileSystemWatcher(lua::get<const QStringList&>(state, 1)));
        } else {
            lua::push(state, new QFileSystemWatcher(lua::get<QObject*>(state, 1)));
        }
        break;
    default:
        // QFileSystemWatcher(const QStringList & paths, QObject * parent = 0)
        lua::push(state, new QFileSystemWatcher(
            lua::get<const QStringList&>(state, 1),
            lua::get<QObject*>(state, 2)
        ));
        break;
    }
    return 1;
}

int luaopen_Qt5Core_QFileSystemWatcher(lua_State* const state)
{
    lua::thread env(state);

    env["QFileSystemWatcher"] = lua::value::table;
    env["QFileSystemWatcher"]["new"] = QFileSystemWatcher_new;
    auto t = env["QFileSystemWatcher"];

    return 0;
}
