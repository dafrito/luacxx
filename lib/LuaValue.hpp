#ifndef HEADER_LUAVALUE_HPP
#define HEADER_LUAVALUE_HPP

#include <string>
#include <cstring>
#include "LuaStack.hpp"
#include "LuaAccessible.hpp"
#include "types.hpp"

using std::string;

class Lua;

class LuaValue
{
protected:
    Lua& lua;

    virtual void push(LuaStack& stack) const=0;

    virtual const LuaAccessible& accessor() const=0;

    lua_State* luaState() const
    {
        return lua.state;
    }
public:
    LuaValue(Lua& lua) :
        lua(lua)
    {}

    lua::Type type()
    {
        LuaStack stack(lua);
        push(stack);
        return stack.type();
    }

    string typestring()
    {
        LuaStack stack(lua);
        push(stack);
        return stack.typestring();
    }

    template <typename T>
    void to(T* value) const
    {
        LuaStack stack(lua);
        push(stack);
        stack.to(value);
    }

    template<typename T>
    operator T() const
    {
        T t;
        this->to(&t);
        return t;
    }

    template<typename T>
    bool operator==(const T& other) const
    {
        // FIXME This does not support comparing to other LuaValues.
        return other == static_cast<T>(*this);
    }

    template <typename... Args>
    LuaStack operator()(Args... args)
    {
        LuaStack stack(lua);
        accessor().push(stack);
        callLua(luaState(), stack, args...);
        return stack;
    }

private:
    friend class LuaStack;
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
void callLua(lua_State* s, LuaStack& stack, Args... args)
{
    typedef std::tuple<Args...> ArgTuple;
    ArgTuple argTuple(args...);
    Pusher<sizeof...(Args), 0>::push(stack, argTuple);
    // Call Lua function. LUA_MULTRET ensures all arguments
    // are returned
    lua_call(s, sizeof...(Args), LUA_MULTRET);
}

#endif
