#include "BasicBlock.hpp"
#include "../../convert/callable.hpp"
#include "../../convert/const_char_p.hpp"
#include "../../thread.hpp"

namespace lua {

void BasicBlock_metatable(lua_State* const state, const int pos)
{
    lua::index mt(state, pos);
    // TODO Set up metatable methods for this class
}

} // namespace lua

int BasicBlock_new(lua_State* const state)
{
    lua::make<BasicBlock>(state);
    // TODO Set up constructor

    return 1;
}

int luaopen_luacxx_BasicBlock(lua_State* const state)
{
    lua::thread env(state);

    env["BasicBlock"] = lua::value::table;
    env["BasicBlock"]["new"] = BasicBlock_new;
    auto t = env["BasicBlock"];

    return 0;
}
