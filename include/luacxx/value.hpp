#ifndef luacxx_value_INCLUDED
#define luacxx_value_INCLUDED

#include "stack.hpp"

// `lua::value` is a small enum for pushing Lua-specific values such as a fresh
// table, `nil`, the globals table, or the registry. See
// docs/guide/working-with-lua-values.md for usage notes.

namespace lua {

enum class value {
    nil = LUA_TNIL,
    table = LUA_TTABLE,
    globals = LUA_RIDX_MAINTHREAD,
    thread = LUA_TTHREAD,
    registry = LUA_REGISTRYINDEX
};

template <>
struct Push<lua::value>
{
    static void push(lua_State* const state, const lua::value& value)
    {
        switch (value) {
            case lua::value::table:
                lua_newtable(state);
                break;
            case lua::value::globals:
                lua_pushglobaltable(state);
                break;
            case lua::value::nil:
                lua_pushnil(state);
                break;
            case lua::value::thread:
                lua_newthread(state);
                break;
            case lua::value::registry:
                lua_pushvalue(state, LUA_REGISTRYINDEX);
                break;
        }
    }
};

} // namespace lua

#endif // luacxx_value_INCLUDED
