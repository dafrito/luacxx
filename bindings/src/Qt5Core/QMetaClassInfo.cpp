#include "QMetaClassInfo.hpp"
#include "../convert/callable.hpp"
#include "../convert/const_char_p.hpp"
#include "../thread.hpp"

namespace lua {

void QMetaClassInfo_metatable(lua_State* const state, const int pos)
{
    lua::index mt(state, pos);
    mt["name"] = &QMetaClassInfo::name;
    mt["value"] = &QMetaClassInfo::value;
}

} // namespace lua

int luaopen_Qt5Core_QMetaClassInfo(lua_State* const state)
{
    lua::thread env(state);

    env["QMetaClassInfo"] = lua::value::table;

    return 0;
}
