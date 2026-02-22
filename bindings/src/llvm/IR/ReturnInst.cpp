#include "ReturnInst.hpp"
#include "../convert/callable.hpp"
#include "../convert/const_char_p.hpp"
#include "../thread.hpp"

namespace lua {

void ReturnInst_metatable(lua_State* const state, const int pos)
{
    lua::index mt(state, pos);
    // TODO Set up metatable methods for this class
}

} // namespace lua

int ReturnInst_new(lua_State* const state)
{
    lua::make<ReturnInst>(state);
    // TODO Set up constructor

    return 1;
}

int luaopen_luacxx_ReturnInst(lua_State* const state)
{
    lua::thread env(state);

    env["ReturnInst"] = lua::value::table;
    env["ReturnInst"]["new"] = ReturnInst_new;
    auto t = env["ReturnInst"];

    return 0;
}
