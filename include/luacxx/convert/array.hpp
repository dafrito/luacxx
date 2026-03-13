#ifndef luacxx_convert_array_INCLUDED
#define luacxx_convert_array_INCLUDED

#include "../stack.hpp"

#include <array>
#include <iostream>

namespace lua {

template <class T, std::size_t N>
struct Push<std::array<T, N>>
{
    static void push(lua_State* const state, const std::array<T, N>& source)
    {
        lua_createtable(state, source.size(), 0);

        for (std::size_t i = 0; i < source.size(); ++i) {
            lua::push(state, source[i]);
            lua_rawseti(state, -2, i + 1);
        }
    }
};

template <class T, std::size_t N>
struct Store<std::array<T, N>>
{
    static void store(std::array<T, N>& destination, lua_State* const state, const int pos)
    {
        lua::index source(state, pos);

        if (!source || !source.type().table()) {
            std::stringstream str;
            str << "Lua stack value at position " << source.pos();
            str << " must be a table, if it is to be converted to a std::array<T, N>";
            throw lua::error(str.str());
        }

        auto num_elements = lua_rawlen(source.state(), source.pos());
        if (num_elements != N) {
            std::stringstream str;
            str << "Lua table at position " << source.pos();
            str << " must contain exactly " << N;
            str << " elements, if it is to be converted to a std::array<T, N>";
            throw lua::error(str.str());
        }

        for (lua_Unsigned i = 1; i <= num_elements; ++i) {
            lua_rawgeti(source.state(), source.pos(), i);
            lua::store(destination[i - 1], source.state(), -1);
            lua_pop(source.state(), 1);
        }
    }
};

} // namespace lua

#endif // luacxx_convert_array_INCLUDED
