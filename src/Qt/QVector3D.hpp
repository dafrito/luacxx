#ifndef LUA_CXX_QVECTOR3D_INCLUDED
#define LUA_CXX_QVECTOR3D_INCLUDED

#include "../lua-cxx/stack.hpp"

class QVector3D;

namespace lua {

void QVector3D_metatable(const lua::index& mt);

template <>
struct Metatable<QVector3D>
{
    static constexpr const char* name = "QVector3D";

    static bool metatable(const lua::index& mt, QVector3D* const)
    {
        lua::QVector3D_metatable(mt);
        return true;
    }
};

}; // namespace lua

extern "C" int luaopen_luacxx_QVector3D(lua_State* const);

#endif // LUA_CXX_QVECTOR3D_INCLUDED
