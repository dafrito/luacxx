#ifndef LUAREFERENCE_HPP
#define LUAREFERENCE_HPP

#include <tuple>
#include "LuaValue.hpp"
#include "Lua.hpp"
#include "LuaReferenceAccessible.hpp"

class LuaReference : public LuaValue
{
    const LuaReferenceAccessible _accessor;

protected:
    void push(LuaStack& stack) const
    {
        accessor().push(stack);
    }

    const LuaAccessible& accessor() const
    {
        return _accessor;
    }

public:
    LuaReference(Lua& lua) :
        LuaValue(lua),
        _accessor(lua)
    {}

    template<typename T>
    const LuaReference& operator=(const T& value)
    {
        LuaStack s(lua);
        s.push(value);
        accessor().store(s);
        return *this;
    }

    template <typename... Args>
    LuaReference operator()(Args... args)
    {
        LuaStack stack(lua);
        accessor.push(stack);
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
