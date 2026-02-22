#include "Value.hpp"
#include "../convert/callable.hpp"
#include "../convert/const_char_p.hpp"
#include "../thread.hpp"

namespace lua {

void Value_metatable(lua_State* const state, const int pos)
{
    lua::index mt(state, pos);
    // TODO Set up metatable methods for this class
}

} // namespace lua

int Value_new(lua_State* const state)
{
    lua::make<Value>(state);
    // TODO Set up constructor

    return 1;
}

int luaopen_luacxx_Value(lua_State* const state)
{
    lua::thread env(state);

    env["Value"] = lua::value::table;
    env["Value"]["new"] = Value_new;
    auto t = env["Value"];

    return 0;
}
