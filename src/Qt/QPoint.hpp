#ifndef LUA_CXX_QPOINT_INCLUDED
#define LUA_CXX_QPOINT_INCLUDED

#include "../lua-cxx/stack.hpp"

class QPoint;

namespace lua {

void QPoint_metatable(const lua::index& mt);

template <>
struct Metatable<QPoint>
{
    static constexpr const char* name = "QPoint";

    static bool metatable(const lua::index& mt, QPoint* const)
    {
        lua::QPoint_metatable(mt);
        return true;
    }
};

}; // namespace lua

extern "C" int luaopen_luacxx_QPoint(lua_State* const);

#endif // LUA_CXX_QPOINT_INCLUDED
