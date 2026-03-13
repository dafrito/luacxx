#ifndef luacxx_convert_optional_INCLUDED
#define luacxx_convert_optional_INCLUDED

#include "../stack.hpp"

#include <optional>

namespace lua {

template <class T>
struct Push<std::optional<T>>
{
    static void push(lua_State* const state, const std::optional<T>& source)
    {
        if (source.has_value()) {
            lua::push(state, *source);
        } else {
            lua_pushnil(state);
        }
    }
};

template <class T>
struct Store<std::optional<T>>
{
    static void store(std::optional<T>& destination, lua_State* const state, const int pos)
    {
        lua::index source(state, pos);

        if (!source || source.type().nil()) {
            destination.reset();
            return;
        }

        destination = lua::get<T>(source.state(), source.pos());
    }
};

template <class T>
struct Get<std::optional<T>>
{
    static std::optional<T> get(lua_State* const state, const int pos)
    {
        lua::index source(state, pos);

        if (!source || source.type().nil()) {
            return std::nullopt;
        }

        return lua::get<T>(source.state(), source.pos());
    }
};

} // namespace lua

#endif // luacxx_convert_optional_INCLUDED
