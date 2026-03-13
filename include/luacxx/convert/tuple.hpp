#ifndef luacxx_convert_tuple_INCLUDED
#define luacxx_convert_tuple_INCLUDED

#include "../stack.hpp"

#include <iostream>
#include <tuple>
#include <utility>

namespace lua {

template <class... Ts>
struct Push<std::tuple<Ts...>>
{
    static void push(lua_State* const state, const std::tuple<Ts...>& source)
    {
        lua_createtable(state, sizeof...(Ts), 0);
        push_impl(state, source, std::index_sequence_for<Ts...>{});
    }

private:
    template <std::size_t... I>
    static void push_impl(lua_State* const state, const std::tuple<Ts...>& source, std::index_sequence<I...>)
    {
        (
            (lua::push(state, std::get<I>(source)),
             lua_rawseti(state, -2, I + 1)),
            ...
        );
    }
};

template <class... Ts>
struct Store<std::tuple<Ts...>>
{
    static void store(std::tuple<Ts...>& destination, lua_State* const state, const int pos)
    {
        lua::index source(state, pos);

        if (!source || !source.type().table()) {
            std::stringstream str;
            str << "Lua stack value at position " << source.pos();
            str << " must be a table, if it is to be converted to a std::tuple<Ts...>";
            throw lua::error(str.str());
        }

        auto num_elements = lua_rawlen(source.state(), source.pos());
        if (num_elements != sizeof...(Ts)) {
            std::stringstream str;
            str << "Lua table at position " << source.pos();
            str << " must contain exactly " << sizeof...(Ts);
            str << " elements, if it is to be converted to a std::tuple<Ts...>";
            throw lua::error(str.str());
        }

        store_impl(destination, source.state(), source.pos(), std::index_sequence_for<Ts...>{});
    }

private:
    template <std::size_t... I>
    static void store_impl(std::tuple<Ts...>& destination, lua_State* const state, const int pos, std::index_sequence<I...>)
    {
        (
            [&] {
                lua_rawgeti(state, pos, I + 1);
                lua::store(std::get<I>(destination), state, -1);
                lua_pop(state, 1);
            }(),
            ...
        );
    }
};

template <class... Ts>
struct Get<std::tuple<Ts...>>
{
    static std::tuple<Ts...> get(lua_State* const state, const int pos)
    {
        std::tuple<Ts...> destination;
        lua::Store<std::tuple<Ts...>>::store(destination, state, pos);
        return destination;
    }
};

} // namespace lua

#endif // luacxx_convert_tuple_INCLUDED
