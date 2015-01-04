#include "SwitchInst.hpp"
#include "../convert/callable.hpp"
#include "../convert/const_char_p.hpp"
#include "../thread.hpp"

namespace lua {

void SwitchInst_metatable(lua_State* const state, const int pos)
{
    lua::index mt(state, pos);
    // TODO Set up metatable methods for this class
}

} // namespace lua

int SwitchInst_new(lua_State* const state)
{
    lua::make<SwitchInst>(state);
    // TODO Set up constructor

    return 1;
}

int luaopen_luacxx_SwitchInst(lua_State* const state)
{
    lua::thread env(state);

    env["SwitchInst"] = lua::value::table;
    env["SwitchInst"]["new"] = SwitchInst_new;
    auto t = env["SwitchInst"];

    return 0;
}
