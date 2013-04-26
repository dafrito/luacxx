#ifndef HEADER_LUAVALUE_HPP
#define HEADER_LUAVALUE_HPP

#include <string>
#include <cstring>

#include "types.hpp"
#include "LuaStack.hpp"
#include "LuaException.hpp"
#include "LuaTableAccessible.hpp"

// LuaValue has a default template parameter, defined in LuaStack.hpp
template <class Accessible>
class LuaValue
{
    Lua& _lua;

    lua_State* luaState() const
    {
        return _lua.luaState();
    }

    Accessible _accessible;

    LuaAccessible& accessor()
    {
        return lua::retrieveAccessor(_accessible);
    }

    const LuaAccessible& accessor() const
    {
        return lua::retrieveAccessor(_accessible);
    }

public:
    LuaValue(Lua& lua, const Accessible& accessible) :
        _lua(lua),
        _accessible(accessible)
    {}

    Lua& lua()
    {
        return _lua;
    }

    void push(LuaStack& stack) const
    {
        accessor().push(stack);
    }

    bool isNil()
    {
        LuaStack stack(_lua);
        push(stack);
        return stack.isNil();
    }

    lua::Type type()
    {
        LuaStack stack(_lua);
        push(stack);
        return stack.type();
    }

    std::string typestring()
    {
        LuaStack stack(_lua);
        push(stack);
        return stack.typestring();
    }

    template <typename Sink>
    void to(Sink& sink) const
    {
        LuaStack stack(_lua);
        push(stack);
        stack >> sink;
    }

    template<typename T>
    operator T() const
    {
        return as<T>();
    }

    template<typename Sink>
    Sink as() const
    {
        Sink sink;
        to(sink);
        return sink;
    }

    const LuaValue& operator=(const LuaValue& other)
    {
        if (&other == this) {
            return *this;
        }
        LuaStack s(_lua);
        lua::push(s, other);
        s >> *this;
        return *this;
    }

    template<typename T>
    const LuaValue& operator=(const T& value)
    {
        LuaStack s(_lua);
        lua::push(s, value);
        accessor().store(s);
        return *this;
    }

    template<typename T>
    const LuaValue& operator=(T& value)
    {
        LuaStack s(_lua);
        lua::push(s, value);
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
    LuaReference operator()(Args&&... args)
    {
        LuaStack stack(_lua);
        push(stack);
        stack.invoke(args...);

        if (stack.empty()) {
            // The called function didn't return anything, so push a nil
            // so we can save an empty reference.
            lua::push(stack, lua::value::nil);
        }

        return stack.save();
    }

    template <typename Key>
    LuaTableValue<Key, Accessible> operator[](Key key)
    {
        LuaTableAccessible<Key, Accessible> tableAccessor(_accessible, key);
        return LuaValue<decltype(tableAccessor)>(lua(), tableAccessor);
    }

    int length()
    {
        LuaStack stack(_lua);

        accessor().push(stack);
        return stack.length();
    }
};

namespace lua {

template <class Accessible>
struct PushOverride<LuaValue<Accessible>>
{
    static constexpr bool value = true;

    static void push(LuaStack& stack, const LuaValue<Accessible>& value)
    {
        value.push(stack);
    }
};

} // namespace lua

template<class Accessible>
LuaIndex& operator>>(LuaIndex& index, LuaValue<Accessible>& sink)
{
    LuaStack& stack = index.stack();
    stack.pushCopy(index.pos());
    sink.accessor().store(stack);
    stack.pop();
    return index;
}

#endif
