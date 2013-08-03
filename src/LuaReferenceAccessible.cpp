#include "LuaReferenceAccessible.hpp"
#include "LuaStack.hpp"

void LuaReferenceAccessible::push(LuaStack&) const
{
    _reference->push();
}

void LuaReferenceAccessible::store(LuaStack& stack) const
{
    _reference->store();
}
