#include "QBackingStore.hpp"
#include "../type/function.hpp"
#include "../thread.hpp"
#include "QSize.hpp"
#include "QRegion.hpp"
#include "QRect.hpp"

#include <QBackingStore>

void* QBackingStore_handle(QBackingStore* const store)
{
    return store->handle();
}

int QBackingStore_flush(lua_State* const state)
{
    auto store = lua::get<QBackingStore*>(state, 1);
    auto region = lua::get<QRegion>(state, 2);

    switch (lua_gettop(state)) {
        case 2:
            store->flush(region);
            break;
        case 3:
            store->flush(region, lua::get<QWindow*>(state, 3));
            break;
        default:
            store->flush(region, lua::get<QWindow*>(state, 3), lua::get<QPoint>(state, 4));
    }

    return 0;
}

void lua::QBackingStore_metatable(const lua::index& mt)
{
    mt["beginPaint"] = &QBackingStore::beginPaint;
    mt["endPaint"] = &QBackingStore::endPaint;
    mt["flush"] = QBackingStore_flush;
    mt["handle"] = QBackingStore_handle;
    mt["hasStaticContents"] = &QBackingStore::hasStaticContents;
    mt["paintDevice"] = &QBackingStore::paintDevice;
    mt["resize"] = &QBackingStore::resize;
    mt["scroll"] = &QBackingStore::scroll;
    mt["setStaticContents"] = &QBackingStore::setStaticContents;
    mt["size"] = &QBackingStore::size;
    mt["staticContents"] = &QBackingStore::staticContents;
    mt["window"] = &QBackingStore::window;
}

int QBackingStore_new(lua_State* const state)
{
    lua::make<QBackingStore>(state, lua::get<QWindow*>(state, 2));
    return 1;
}

int luaopen_luacxx_QBackingStore(lua_State* const state)
{
    lua::thread env(state);

    env["QBackingStore"] = lua::value::table;
    env["QBackingStore"]["new"] = QBackingStore_new;

    return 0;
}
