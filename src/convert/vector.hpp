#ifndef luacxx_convert_vector_INCLUDED
#define luacxx_convert_vector_INCLUDED

#include "../stack.hpp"

#include <vector>
#include <iostream>

namespace lua {

template <class T>
struct Push<std::vector<T>>
{
    static void push(lua_State* const state, const std::vector<T>& source)
    {
        // Create a new table and get an absolute index
        lua_createtable(state, source.size(), 0);

        // Populate the table with each value in source
        for (int i = 0; i < source.size(); ++i) {
            lua::push(state, source[i]);
            lua_rawseti(state, -2, i + 1);
        }
    }
};

template <class T>
struct Store<std::vector<T>>
{
    static void store(std::vector<T>& destination, lua_State* const state, const int pos)
    {
        lua::index source(state, pos);

        if (!source || !source.type().table()) {
            std::stringstream str;
            str << "Lua stack value at position " << source.pos();
            str << " must be a table, if it is to be converted to a std::vector<T>";
            throw lua::error(str.str());
        }

        auto num_elements = lua_rawlen(source.state(), source.pos());
        auto target_index = destination.size();
        destination.resize(destination.size() + num_elements);

        for (int i = 1; i <= num_elements; ++i, ++target_index) {
            lua_rawgeti(source.state(), source.pos(), i);
            lua::store(destination[target_index], source.state(), -1);
            lua_pop(source.state(), 1);
        }
    }
};

} // namespace lua

#endif // luacxx_convert_vector_INCLUDED
