#include "QVariantMap.hpp"
#include "../convert/callable.hpp"
#include "../convert/const_char_p.hpp"
#include "../thread.hpp"

#include "QMap.hpp"

namespace lua {

void QVariantMap_metatable(lua_State* const state, const int pos)
{
    lua::QMap_metatable<QString, QVariant>(state, pos);
}

} // namespace lua

int QVariantMap_new(lua_State* const state)
{
    lua::make<QVariantMap>(state);

    return 1;
}

int luaopen_luacxx_QVariantMap(lua_State* const state)
{
    lua::thread env(state);

    env["QVariantMap"] = lua::value::table;
    env["QVariantMap"]["new"] = QVariantMap_new;
    auto t = env["QVariantMap"];

    return 0;
}
