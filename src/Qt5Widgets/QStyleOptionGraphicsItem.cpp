#include "QStyleOptionGraphicsItem.hpp"
#include "../convert/callable.hpp"
#include "../thread.hpp"

namespace lua {

void QStyleOptionGraphicsItem_metatable(lua_State* const state, const int pos)
{
    lua::QStyleOption_metatable(state, pos);

    lua::index mt(state, pos);

    // TODO Public Variables
    // QRectF   exposedRect
}

} // namespace lua

int QStyleOptionGraphicsItem_new(lua_State* const state)
{
    // TODO QStyleOptionGraphicsItem
    lua::make<QStyleOptionGraphicsItem>(state);
    return 1;
}

int luaopen_luacxx_QStyleOptionGraphicsItem(lua_State* const state)
{
    lua::thread env(state);

    env["QStyleOptionGraphicsItem"] = lua::value::table;
    env["QStyleOptionGraphicsItem"]["new"] = QStyleOptionGraphicsItem_new;
    auto t = env["QStyleOptionGraphicsItem"];

    return 0;
}
