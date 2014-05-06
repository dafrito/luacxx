#ifndef LUA_CXX_TYPE_HEADER
#define LUA_CXX_TYPE_HEADER

#include <lua.hpp>

namespace lua {

class type_info;

enum class type {
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

class type_info
{
    lua::type _value;

public:

    type_info(lua::type value) :
        _value(value)
    {
    }

    const char* name() const {
        // Lua provides lua_typename for this behavior presumably to allow
        // localization, but I prefer just having these be inline here as
        // they're usually just used for debugging purposes.

        switch (get()) {
            case lua::type::nil:           return "nil";
            case lua::type::boolean:       return "boolean";
            case lua::type::number:        return "number";
            case lua::type::string:        return "string";
            case lua::type::table:         return "table";
            case lua::type::function:      return "function";
            case lua::type::thread:        return "thread";
            case lua::type::userdata:      return "userdata";
            case lua::type::lightuserdata: return "lightuserdata";
            default:                       return "";
        }
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
        return get() == lua::type::nil;
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

    const lua::type get() const
    {
        return _value;
    }
};

} // namespace lua

#endif // LUA_CXX_TYPE_HEADER
