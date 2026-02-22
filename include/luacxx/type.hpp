#ifndef luacxx_type_INCLUDED
#define luacxx_type_INCLUDED

#include <string_view>
#include <ostream>

#include <lua.hpp>

namespace lua {

class type_info;

enum class type {
    none = LUA_TNONE,
    nil = LUA_TNIL,
    boolean = LUA_TBOOLEAN,
    number = LUA_TNUMBER,
    string = LUA_TSTRING,
    table = LUA_TTABLE,
    function = LUA_TFUNCTION,
    userdata = LUA_TUSERDATA,
    lightuserdata = LUA_TLIGHTUSERDATA,
    thread = LUA_TTHREAD
};

constexpr std::string_view to_string(type value) noexcept
{
    // Lua provides lua_typename, but that requires a lua_State
    // and I'd like this to work without one.
    using enum type; // C++20; optional
    switch (value) {
        case none:          return "no value";
        case nil:           return "nil";
        case boolean:       return "boolean";
        case number:        return "number";
        case string:        return "string";
        case table:         return "table";
        case function:      return "function";
        case thread:        return "thread";
        case userdata:      return "userdata";
        case lightuserdata: return "light userdata";
    }
    return "unknown";
}

inline std::ostream& operator<<(std::ostream& os, type value) {
    return os << to_string(value);
}

class type_info
{
    lua::type _value;

public:

    type_info(lua::type value) :
        _value(value)
    {
    }

    type_info(int value) :
        type_info(static_cast<lua::type>(value))
    {
    }

    std::string_view name() const {
      return to_string(get());
    }

    bool operator==(const lua::type_info& other) const
    {
        return get() == other.get();
    }

    bool operator==(const lua::type& other) const
    {
        return get() == other;
    }

    template <class Type>
    bool operator!=(const Type& other) const
    {
        return !(*this == other);
    }

    bool nil() const
    {
        return get() == lua::type::nil || get() == lua::type::none;
    }

    bool none() const
    {
        return get() == lua::type::none;
    }

    bool boolean() const
    {
        return get() == lua::type::boolean;
    }

    bool string() const
    {
        return get() == lua::type::string;
    }

    bool number() const
    {
        return get() == lua::type::number;
    }

    bool table() const
    {
        return get() == lua::type::table;
    }

    bool function() const
    {
        return get() == lua::type::function;
    }

    bool userdata() const
    {
        return get() == lua::type::userdata;
    }

    bool thread() const
    {
        return get() == lua::type::thread;
    }

    bool lightuserdata() const
    {
        return get() == lua::type::lightuserdata;
    }

    lua::type get() const
    {
        return _value;
    }
};

inline std::ostream& operator<<(std::ostream& os, const type_info& value) {
    return os << value.name();
}

} // namespace lua

#endif // luacxx_type_INCLUDED
