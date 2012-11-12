#ifndef LUAGLOBAL_HPP
#define LUAGLOBAL_HPP

#include "LuaValue.hpp"
#include "LuaReference.hpp"
#include "LuaGlobalAccessible.hpp"

class LuaGlobal : public LuaValue
{
    const LuaGlobalAccessible _accessor;

protected:
    const LuaAccessible& accessor() const
    {
        return _accessor;
    }

public:
    LuaGlobal(Lua& lua, const QString& key) :
        LuaValue(lua),
        _accessor(lua, key)
    {}

    template<typename T>
    const LuaGlobal& operator=(const T& value)
    {
        LuaValue::operator=(value);
        return *this;
    }

};

#endif // LUAGLOBAL_HPP
