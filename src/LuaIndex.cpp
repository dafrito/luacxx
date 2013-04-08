#include "LuaIndex.hpp"
#include "LuaStack.hpp"

LuaIndex::LuaIndex(LuaStack& stack, const int pos, const int direction) :
    _stack(stack),
    _pos(pos),
    _direction(direction)
{
}

LuaStack& LuaIndex::stack() const
{
    return _stack;
}

int LuaIndex::pos() const
{
    return _pos;
}

// Postfix
LuaIndex LuaIndex::operator++(int)
{
    LuaIndex rv(*this);
    ++(*this);
    return rv;
}

LuaIndex& LuaIndex::operator++()
{
    _pos += _direction;
    return *this;
}

// Postfix
LuaIndex LuaIndex::operator--(int)
{
    LuaIndex rv(*this);
    --(*this);
    return rv;
}

LuaIndex& LuaIndex::operator--()
{
    _pos -= _direction;
    return *this;
}
