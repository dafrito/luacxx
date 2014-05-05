#ifndef LUA_CXX_TYPE_HEADER
#define LUA_CXX_TYPE_HEADER

#include <lua.hpp>

namespace lua
{
    class type;
}

class lua::type
{
    int _value;

public:
    type(const int value) :
        _value(value)
    {
    }

    const char* name() const {
        // Lua provides lua_typename for this behavior presumably to allow
        // localization, but I prefer just having these be inline here as
        // they're usually just used for debugging purposes.

        switch (get()) {
            case LUA_TNIL:           return "nil";
            case LUA_TBOOLEAN:       return "boolean";
            case LUA_TNUMBER:        return "number";
            case LUA_TSTRING:        return "string";
            case LUA_TTABLE:         return "table";
            case LUA_TFUNCTION:      return "function";
            case LUA_TTHREAD:        return "thread";
            case LUA_TUSERDATA:      return "userdata";
            case LUA_TLIGHTUSERDATA: return "lightuserdata";
            default:                 return "";
        }
    }

    bool operator==(const lua::type& other) const
    {
        return get() == other.get();
    }

    bool nil() const
    {
        return get() == LUA_TNIL;
    }

    bool boolean() const
    {
        return get() == LUA_TBOOLEAN;
    }

    bool string() const
    {
        return get() == LUA_TSTRING;
    }

    bool number() const
    {
        return get() == LUA_TNUMBER;
    }

    bool table() const
    {
        return get() == LUA_TTABLE;
    }

    bool function() const
    {
        return get() == LUA_TFUNCTION;
    }

    bool userdata() const
    {
        return get() == LUA_TUSERDATA;
    }

    bool thread() const
    {
        return get() == LUA_TTHREAD;
    }

    bool lightuserdata() const
    {
        return get() == LUA_TLIGHTUSERDATA;
    }

    const int get() const
    {
        return _value;
    }
};

#endif // LUA_CXX_TYPE_HEADER
