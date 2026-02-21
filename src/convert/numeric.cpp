#include "luacxx/algorithm.hpp"
#include "luacxx/convert/numeric.hpp"
#include "luacxx/convert/const_char_p.hpp"

void lua::store_lua_Integer(lua_Integer& destination, lua_State* const state, const int source_pos)
{
    lua::index source(state, source_pos);

    // Directly retrieve boolean types.
    if(source.type().boolean()) {
        destination = static_cast<lua_Integer>(lua_toboolean(source.state(), source.pos()));
        return;
    }

    // Directly retrieve numeric types.
    if(source.type().number()) {
        destination = static_cast<lua_Integer>(lua_tointeger(source.state(), source.pos()));
        return;
    }

    // Convert the first character of a string to its numeric value.
    if(source.type().string()) {
        destination = source.get<const char*>()[0];
        return;
    }

    // Convert userdata to integers by interpreting the data as-is.
    if(source.type().userdata()) {
        auto valueSize = lua::object_size(state, source_pos);
        if(valueSize == sizeof(long long)) {
            destination = static_cast<lua_Integer>(
                *static_cast<long long*>(lua::get<void*>(source))
            );
            return;
        }
        if(valueSize == sizeof(long)) {
            destination = static_cast<lua_Integer>(
                *static_cast<long*>(lua::get<void*>(source))
            );
            return;
        }
        if(valueSize == sizeof(int)) {
            destination = static_cast<lua_Integer>(
                *static_cast<int*>(lua::get<void*>(source))
            );
            return;
        }
        if(valueSize == sizeof(short)) {
            destination = static_cast<lua_Integer>(
                *static_cast<short*>(lua::get<void*>(source))
            );
            return;
        }
        if(valueSize == sizeof(char)) {
            destination = static_cast<lua_Integer>(
                *static_cast<char*>(lua::get<void*>(source))
            );
            return;
        }
        if(valueSize == sizeof(bool)) {
            destination = static_cast<lua_Integer>(
                *static_cast<bool*>(lua::get<void*>(source))
            );
            return;
        }
    }

    // Nothing retrieved, so clear destination.
    destination = 0;
}
