#ifndef LUA_CXX_TYPE_LUAREFERENCE_HPP
#define LUA_CXX_TYPE_LUAREFERENCE_HPP

#include "LuaValue.hpp"

namespace lua {

template <>
struct Getter<LuaValue<LuaReferenceAccessible>>
{
    static LuaReference get(const LuaIndex& index)
    {
        return LuaValue<LuaReferenceAccessible>(
            index.stack().luaState(),
            LuaReferenceAccessible(
                index.stack().luaState(),
                index.stack().save(index.pos())
            )
        );
    }
};


} // namespace lua

#endif // LUA_CXX_TYPE_LUAREFERENCE_HPP
