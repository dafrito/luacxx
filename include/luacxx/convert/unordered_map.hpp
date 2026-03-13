#ifndef luacxx_convert_unordered_map_INCLUDED
#define luacxx_convert_unordered_map_INCLUDED

#include "../stack.hpp"

#include <iostream>
#include <unordered_map>
#include <utility>

namespace lua {

template <class K, class V>
struct Push<std::unordered_map<K, V>>
{
    static void push(lua_State* const state, const std::unordered_map<K, V>& source)
    {
        lua_createtable(state, 0, source.size());

        for (const auto& entry : source) {
            lua::push(state, entry.first);
            lua::push(state, entry.second);
            lua_settable(state, -3);
        }
    }
};

template <class K, class V>
struct Store<std::unordered_map<K, V>>
{
    static void store(std::unordered_map<K, V>& destination, lua_State* const state, const int pos)
    {
        lua::index source(state, pos);

        if (!source || !source.type().table()) {
            std::stringstream str;
            str << "Lua stack value at position " << source.pos();
            str << " must be a table, if it is to be converted to a std::unordered_map<K, V>";
            throw lua::error(str.str());
        }

        destination.clear();

        lua::push(source.state(), lua::value::nil);
        while (lua_next(source.state(), source.pos()) != 0) {
            K key;
            V value;

            lua::store(key, source.state(), -2);
            lua::store(value, source.state(), -1);
            destination[std::move(key)] = std::move(value);

            lua_pop(source.state(), 1);
        }
    }
};

} // namespace lua

#endif // luacxx_convert_unordered_map_INCLUDED
