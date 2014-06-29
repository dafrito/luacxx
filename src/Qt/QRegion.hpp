#ifndef LUA_CXX_QREGION_INCLUDED
#define LUA_CXX_QREGION_INCLUDED

#include "../lua-cxx/stack.hpp"

class QRegion;

namespace lua {

void QRegion_metatable(const lua::index& mt);

template <>
struct Metatable<QRegion>
{
    static constexpr const char* name = "QRegion";

    static bool metatable(const lua::index& mt, QRegion* const)
    {
        lua::QRegion_metatable(mt);
        return true;
    }
};

}; // namespace lua

extern "C" int luaopen_luacxx_QRegion(lua_State* const);

#endif // LUA_CXX_QREGION_INCLUDED
