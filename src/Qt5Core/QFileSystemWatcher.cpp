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
    // QFileSystemWatcher(QObject * parent = 0)
    // QFileSystemWatcher(const QStringList & paths, QObject * parent = 0)
    if (lua_gettop(state) > 0) {
        lua::make<QFileSystemWatcher>(state, lua::get<const QStringList&>(state, 1));
    } else {
        lua::make<QFileSystemWatcher>(state);
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
