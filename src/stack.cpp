#include "stack.hpp"
#include "algorithm.hpp"

template <>
void lua::get<void>(const lua::index& source)
{
}

// Allow noop invocations from variadic templates
lua::index lua::push(lua::state* const state)
{
    return lua::index(state, -1);
}

int lua::__gc(lua::state* const state)
{
    char* block = static_cast<char*>(lua_touserdata(state, 1));
    auto userdata = reinterpret_cast<lua::userdata_block*>(block);

    lua_getmetatable(state, 1);
    auto mt = lua::index(state, -1);

    auto destroy = lua::table::get(mt, "Destroy");
    if (destroy.type().function()) {
        lua::call(destroy, lua::index(state, 1));
    }

    userdata->~userdata_block();

    return 0;
}

