#include "LuaStack.hpp"

void LuaReferenceAccessible::push(LuaStack&) const
{
    _reference->push();
}

void LuaReferenceAccessible::store(LuaStack& stack) const
{
    // Push a copy since the store will pop the topmost value.
    stack.pushCopy();
    _reference->store();
}
