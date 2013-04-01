#ifndef HEADER_LUAVALUE_HPP
#define HEADER_LUAVALUE_HPP

#include <string>
#include <cstring>
#include "LuaStack.hpp"
#include "LuaAccessible.hpp"
#include "LuaTableAccessible.hpp"
#include "types.hpp"

#include <memory>

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

    string typestring()
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
    LuaValue operator()(Args&&... args)
    {
        LuaStack stack(_lua);
        push(stack);
        callLua(luaState(), stack, args...);

        if (stack.empty()) {
            // The called function didn't return anything, so push a nil
            // so we can save an empty reference.
            stack << lua::value::nil;
        }

        return stack.save();
    }

    template <typename T>
    LuaValue operator[](T key)
    {
        return LuaValue(
            std::shared_ptr<LuaAccessible>(
                new LuaTableAccessible<T>(lua(), accessible, key)
            )
        );
    }

    int length()
    {
        LuaStack stack(_lua);

        accessor().push(stack);
        return stack.length();
    }

    static void callLua(lua_State* s, LuaStack& stack)
    {
        // Call Lua function. LUA_MULTRET ensures all arguments are returned
        // Subtract one from the size to ignore the function itself and pass
        // the correct number of arguments
        lua_call(s, stack.size() - 1, LUA_MULTRET);
    }

    template <typename Arg, typename... Rest>
    static void callLua(lua_State* s, LuaStack& stack, Arg&& arg, Rest&&... rest)
    {
        stack << arg;
        callLua(s, stack, rest...);
    }

private:
    friend class LuaStack;
};

#endif
