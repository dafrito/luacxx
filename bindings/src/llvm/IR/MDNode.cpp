#include "MDNode.hpp"
#include "../convert/callable.hpp"
#include "../convert/const_char_p.hpp"
#include "../thread.hpp"

namespace lua {

void MDNode_metatable(lua_State* const state, const int pos)
{
    lua::index mt(state, pos);
    // TODO Set up metatable methods for this class
}

} // namespace lua

int MDNode_new(lua_State* const state)
{
    lua::make<MDNode>(state);
    // TODO Set up constructor

    return 1;
}

int luaopen_luacxx_MDNode(lua_State* const state)
{
    lua::thread env(state);

    env["MDNode"] = lua::value::table;
    env["MDNode"]["new"] = MDNode_new;
    auto t = env["MDNode"];

    return 0;
}
