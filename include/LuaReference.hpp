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
    const LuaAccessible& accessor() const
    {
        return _accessor;
    }

public:
    explicit LuaReference(Lua& lua) :
        LuaValue(lua),
        _accessor(lua)
    {}

    template<typename T>
    const LuaReference& operator=(const T& value)
    {
        LuaValue::operator=(value);
        return *this;
    }
};

#endif // LUAREFERENCE_HPP
