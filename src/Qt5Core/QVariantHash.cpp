#include "QVariantHash.hpp"
#include "../convert/callable.hpp"
#include "../convert/const_char_p.hpp"
#include "../thread.hpp"

#include "QHash.hpp"

namespace lua {

void QVariantHash_metatable(lua_State* const state, const int pos)
{
    lua::QHash_metatable<QString, QVariant>(state, pos);
}

} // namespace lua

int QVariantHash_new(lua_State* const state)
{
    lua::make<QVariantHash>(state);

    return 1;
}

int luaopen_luacxx_QVariantHash(lua_State* const state)
{
    lua::thread env(state);

    env["QVariantHash"] = lua::value::table;
    env["QVariantHash"]["new"] = QVariantHash_new;
    auto t = env["QVariantHash"];

    return 0;
}
