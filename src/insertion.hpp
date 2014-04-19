#include "LuaStack.hpp"

template <typename Source>
LuaStack& operator<<(LuaStack& stack, Source& value)
{
    lua::push(stack, value);
    return stack;
}

template <typename Source>
LuaStack& operator<<(LuaStack& stack, const Source& value)
{
    lua::push(stack, value);
    return stack;
}
