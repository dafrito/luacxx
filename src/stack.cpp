#include "stack.hpp"
#include "algorithm.hpp"
#include <iostream>

template <>
void lua::get<void>(const lua::index& source)
{
}

// Allow noop invocations from variadic templates
lua::index lua::push(lua_State* const state)
{
    return lua::index(state, -1);
}

int lua::__gc(lua_State* const state)
{
    char* block = static_cast<char*>(lua_touserdata(state, 1));
    auto userdata = reinterpret_cast<lua::userdata_block*>(block);

    lua_getmetatable(state, 1);
    auto mt = lua::index(state, -1);

    try {
        auto destroy = lua::table::get(mt, "destroy");
        if (destroy.type().function()) {
            lua::call(destroy, lua::index(state, 1));
        }

        auto free_userdata = lua::table::get(mt, "free_userdata");
        if (free_userdata.type().function()) {
            lua::call(free_userdata, lua::index(state, 1));
        }

        userdata->~userdata_block();
    } catch (lua::error& ex) {
        std::cerr << "Error occurred during Lua garbage collection: " << ex.what();
    }

    return 0;
}
