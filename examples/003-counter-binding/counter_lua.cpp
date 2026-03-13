#include "counter_lua.hpp"

#include <luacxx/algorithm.hpp>
#include <luacxx/convert/callable.hpp>
#include <luacxx/convert/const_char_p.hpp>
#include <luacxx/convert/numeric.hpp>
#include <luacxx/thread.hpp>
#include <luacxx/value.hpp>

void lua::Counter_metatable(lua_State* const state, const int mt)
{
    lua::index table(state, mt);
    table["add"] = &Counter::add;
    table["get"] = &Counter::get;
}

int Counter_new(lua_State* const state)
{
    const int initial = lua_gettop(state) >= 1 ? lua::get<int>(state, 1) : 0;
    lua::make<Counter>(state, initial);
    return 1;
}

void open_counter(lua_State* const state)
{
    lua::thread env(state);
    env["Counter"] = lua::value::table;
    env["Counter"]["new"] = Counter_new;
}
