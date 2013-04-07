#include "LuaGlobalAccessible.hpp"

LuaGlobalAccessible::LuaGlobalAccessible(const QString& key) :
    key(key)
{}

void LuaGlobalAccessible::push(LuaStack& stack) const
{
    stack.global(key);
}

void LuaGlobalAccessible::store(LuaStack& stack) const
{
    stack.setGlobal(key);
    push(stack);
}
