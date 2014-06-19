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

char* lua::malloc(lua_State* const state, size_t size, const lua::userdata_block& userdata_block)
{
    // Get and push a chunk of memory from Lua to hold our metadata, as well as
    // the underlying value.
    char* block = static_cast<char*>(lua_newuserdata(state,
        size + sizeof(lua::userdata_block)
    ));

    // Create the metadata at the end of the memory block; lua_touserdata will return a
    // valid pointer.
    new (block + size) lua::userdata_block(userdata_block);

    // Return a pointer to the data block
    return block;
}

int lua::__gc(lua_State* const state)
{
    char* block = static_cast<char*>(lua_touserdata(state, 1));
    auto userdata_block = lua::get<lua::userdata_block*>(state, 1);

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

        userdata_block->~userdata_block();
    } catch (lua::error& ex) {
        std::cerr << "Error occurred during Lua garbage collection: " << ex.what();
    }

    return 0;
}
