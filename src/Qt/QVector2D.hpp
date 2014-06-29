#ifndef LUA_CXX_QVECTOR2D_INCLUDED
#define LUA_CXX_QVECTOR2D_INCLUDED

#include "../lua-cxx/stack.hpp"

class QVector2D;

namespace lua {

void QVector2D_metatable(const lua::index& mt);

template <>
struct Metatable<QVector2D>
{
    static constexpr const char* name = "QVector2D";

    static bool metatable(const lua::index& mt, QVector2D* const)
    {
        lua::QVector2D_metatable(mt);
        return true;
    }
};

}; // namespace lua

extern "C" int luaopen_luacxx_QVector2D(lua_State* const);

#endif // LUA_CXX_QVECTOR2D_INCLUDED
