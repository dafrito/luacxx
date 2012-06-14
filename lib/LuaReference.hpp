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
};

#endif // LUAREFERENCE_HPP
