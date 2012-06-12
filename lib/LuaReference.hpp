#ifndef LUAREFERENCE_HPP
#define LUAREFERENCE_HPP

#include <tuple>
#include "LuaValue.hpp"
#include "Lua.hpp"

class LuaReference : public LuaValue
{
    int ref;
protected:
    void push(LuaStack&) const
    {
        lua_rawgeti(luaState(), LUA_REGISTRYINDEX, ref);
    }
public:
    LuaReference(Lua& lua) : LuaValue(lua)
    {
        ref = luaL_ref(luaState(), LUA_REGISTRYINDEX);
    }

    ~LuaReference()
    {
        luaL_unref(luaState(), LUA_REGISTRYINDEX, ref);
    }

    template<typename T>
    const LuaReference& operator=(const T& value)
    {
        LuaStack s(lua);
        s.push(value);
        lua_rawseti(luaState(), LUA_REGISTRYINDEX, ref);
        return *this;
    }

    template <typename... Args>
    LuaReference operator()(Args... args)
    {
        LuaStack stack(lua);
        push(stack);
        return callLua(luaState(), stack, args...);
    }
};

namespace
{
    template <unsigned L, unsigned I>
    struct Pusher
    {
        template <typename Tuple>
        static void push(LuaStack& stack, Tuple& tuple)
        {
            stack.push(std::get<I>(tuple));
            Pusher<L-1, I+1>::push(stack, tuple);
        }
    };

    template <unsigned I>
    struct Pusher<0, I>
    {
        template <typename Tuple>
        static void push(LuaStack&, Tuple&)
        {
        }
    };
}

template <typename... Args>
LuaReference callLua(lua_State* s, LuaStack& stack, Args... args)
{
    typedef std::tuple<Args...> ArgTuple;
    ArgTuple argTuple(args...);
    Pusher<sizeof...(Args), 0>::push(stack, argTuple);
    // Call Lua function.
    lua_call(s, sizeof...(Args), 1);
    return stack.save();
}

#endif // LUAREFERENCE_HPP
