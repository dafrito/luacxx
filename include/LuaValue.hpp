#ifndef HEADER_LUAVALUE_HPP
#define HEADER_LUAVALUE_HPP

#include <string>
#include <cstring>
#include "LuaStack.hpp"
#include "LuaAccessible.hpp"
#include "types.hpp"

#include <memory>

#include <iostream>

using std::string;

class Lua;

class LuaValue
{
    Lua& _lua;

    std::shared_ptr<LuaAccessible> accessible;

    const LuaAccessible& accessor() const
    {
        return (*accessible);
    }

    lua_State* luaState() const
    {
        return _lua.state;
    }
public:
    LuaValue(const std::shared_ptr<LuaAccessible>& accessible) :
        _lua(accessible->lua()),
        accessible(accessible)
    {}

    Lua& lua()
    {
        return _lua;
    }

    void push(LuaStack& stack) const
    {
        accessor().push(stack);
    }

    lua::Type type()
    {
        LuaStack stack(_lua);
        push(stack);
        return stack.type();
    }

    string typestring()
    {
        LuaStack stack(_lua);
        push(stack);
        return stack.typestring();
    }

    template <typename T>
    void to(T* value) const
    {
        LuaStack stack(_lua);
        push(stack);
        stack.to(value);
    }

    template <typename T>
    void to(T& sink)
    {
        return to(&sink);
    }

    template<typename T>
    operator T() const
    {
        T t;
        this->to(&t);
        return t;
    }

    template<typename T>
    const LuaValue& operator=(const T& value)
    {
        LuaStack s(_lua);
        s << value;
        accessor().store(s);
        return *this;
    }

    template<typename T>
    bool operator==(const T& other) const
    {
        // FIXME This does not support comparing to other LuaValues.
        return other == static_cast<T>(*this);
    }

    template <typename... Args>
    LuaValue operator()(Args... args)
    {
        LuaStack stack(_lua);
        accessor().push(stack);
        callLua(luaState(), stack, args...);

        if (stack.empty()) {
            // The called function didn't return anything, so push a nil
            // so we can save an empty reference.
            stack.pushNil();
        }

        return stack.save();
    }

    template <typename T>
    LuaValue operator[](T key)
    {
        LuaStack stack(_lua);

        accessor().push(stack);
        stack.get(key, -1);

        // Shift our table off, so only the value remains.
        stack.shift();

        return stack.save();
    }

    int length()
    {
        LuaStack stack(_lua);

        accessor().push(stack);
        return stack.length();
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
            stack << std::get<I>(tuple);
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
