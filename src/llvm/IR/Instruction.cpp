#include "Instruction.hpp"
#include "../../convert/callable.hpp"
#include "../../convert/const_char_p.hpp"
#include "../../thread.hpp"

namespace lua {

void Instruction_metatable(lua_State* const state, const int pos)
{
    lua::index mt(state, pos);
    // TODO Set up metatable methods for this class
}

} // namespace lua

int Instruction_new(lua_State* const state)
{
    lua::make<Instruction>(state);
    // TODO Set up constructor

    return 1;
}

int luaopen_llvm_Instruction(lua_State* const state)
{
    lua::thread env(state);

    env["Instruction"] = lua::value::table;
    env["Instruction"]["new"] = Instruction_new;
    auto t = env["Instruction"];

    return 0;
}
