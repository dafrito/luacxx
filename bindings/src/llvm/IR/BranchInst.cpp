#include "BranchInst.hpp"
#include "../convert/callable.hpp"
#include "../convert/const_char_p.hpp"
#include "../thread.hpp"

namespace lua {

void BranchInst_metatable(lua_State* const state, const int pos)
{
    lua::index mt(state, pos);
    // TODO Set up metatable methods for this class
}

} // namespace lua

int BranchInst_new(lua_State* const state)
{
    lua::make<BranchInst>(state);
    // TODO Set up constructor

    return 1;
}

int luaopen_luacxx_BranchInst(lua_State* const state)
{
    lua::thread env(state);

    env["BranchInst"] = lua::value::table;
    env["BranchInst"]["new"] = BranchInst_new;
    auto t = env["BranchInst"];

    return 0;
}
