#ifndef luacxx_value_INCLUDED
#define luacxx_value_INCLUDED

#include "stack.hpp"

/*

=head1 NAME

value.hpp - support for fundamental Lua types

=head1 SYNOPSIS

    #include <luacxx/value.hpp>

=head1 DESCRIPTION

This header provides support for all of the core
Lua types, like lua::index, lua::value::*, as well
as the Lua primitive types, like lua_Number and
const char*.

=head4 lua_pushnil(state), lua::value::nil

Pushes a nil value onto the stack.

    #include <luacxx/convert/builtin.hpp>

    lua::push(state, lua::value::nil);
    lua_pushnil(state);

=head4 lua_pushvalue(state, int source), lua::push<lua::index>

Pushes a copy of the stack value at the given source index onto the stack.

    #include <luacxx/convert/builtin.hpp>

    lua::push(state, lua::index(state, 1));
    lua_pushvalue(state, 1);

=head4 lua_pushboolean(state, value), lua::push<bool>

Pushes a boolean value onto the stack.

    #include <luacxx/convert/numeric.hpp>

    lua::push(state, false);
    lua_pushboolean(state, 0);

=head4 lua_newtable(state), lua::value::table

Pushes a new empty table onto the stack.

    #include <luacxx/convert/builtin.hpp>

    lua_newtable(state);
    lua::push(state, lua::value::table);

=head4 lua_pushglobaltable(state), lua::value::globals

Pushes the global environment table onto the stack.

    #include <luacxx/convert/build.hpp>

    lua_pushglobaltable(state);
    lua::push(state, lua::value::globals);

=head4 lua_pushvalue(state, LUA_REGISTRYINDEX), lua::value::registry

Pushes the registry onto the stack.

    #include <luacxx/convert/builtin.hpp>

    lua_pushvalue(state, LUA_REGISTRYINDEX);
    lua::push(state, lua::value::registry);

=head4 lua_pushstring(state, const char*), lua::push<const char*>

    #include <luacxx/convert/string.hpp>

    lua_pushstring(state, "No time");
    lua::push(state, "No time");

*/

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
