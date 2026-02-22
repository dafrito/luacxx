#include "QVariantList.hpp"
#include "../convert/callable.hpp"
#include "../convert/const_char_p.hpp"
#include "../thread.hpp"

#include "QList.hpp"
#include "QVariant.hpp"

namespace lua {

void QVariantList_metatable(lua_State* const state, const int pos)
{
    lua::QList_metatable<QVariant>(state, pos);
}

} // namespace lua

int QVariantList_new(lua_State* const state)
{
    lua::make<QVariantList>(state);

    return 1;
}

int luaopen_luacxx_QVariantList(lua_State* const state)
{
    lua::thread env(state);

    env["QVariantList"] = lua::value::table;
    env["QVariantList"]["new"] = QVariantList_new;
    auto t = env["QVariantList"];

    return 0;
}
