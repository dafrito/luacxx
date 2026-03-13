#ifndef LUACXX_EXAMPLE_COUNTER_LUA_HPP
#define LUACXX_EXAMPLE_COUNTER_LUA_HPP

#include "counter.hpp"

#include <luacxx/stack.hpp>

namespace lua {

void Counter_metatable(lua_State* const state, const int mt);

} // namespace lua

LUA_METATABLE_BUILT_WITH(Counter, lua::Counter_metatable);

int Counter_new(lua_State* const state);
void open_counter(lua_State* const state);

#endif // LUACXX_EXAMPLE_COUNTER_LUA_HPP
