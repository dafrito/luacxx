#include "QAbstractNetworkCache.hpp"
#include "../convert/callable.hpp"
#include "../convert/const_char_p.hpp"
#include "../thread.hpp"

#include "../Qt5Core/QIODevice.hpp"
#include "QNetworkCacheMetaData.hpp"
#include "../Qt5Core/QUrl.hpp"

// http://qt-project.org/doc/qt-5/qabstractnetworkcache.html

namespace lua {

void QAbstractNetworkCache_metatable(lua_State* const state, const int pos)
{
    lua::QObject_metatable(state, pos);

    lua::index mt(state, pos);
    mt["cacheSize"] = &QAbstractNetworkCache::cacheSize;
    mt["data"] = &QAbstractNetworkCache::data;
    mt["insert"] = &QAbstractNetworkCache::insert;
    mt["metaData"] = &QAbstractNetworkCache::metaData;
    mt["prepare"] = &QAbstractNetworkCache::prepare;
    mt["remove"] = &QAbstractNetworkCache::remove;
    mt["updateMetaData"] = &QAbstractNetworkCache::updateMetaData;
}

} // namespace lua

int luaopen_Qt5Network_QAbstractNetworkCache(lua_State* const state)
{
    lua::thread env(state);

    env["QAbstractNetworkCache"] = lua::value::table;
    auto t = env["QAbstractNetworkCache"];

    return 0;
}
