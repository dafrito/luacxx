#ifndef LUA_CXX_QVECTOR4D_INCLUDED
#define LUA_CXX_QVECTOR4D_INCLUDED

#include "../stack.hpp"

class QVector4D;

namespace lua {

void QVector4D_metatable(const lua::index& mt);

template <>
struct Metatable<QVector4D>
{
    static constexpr const char* name = "QVector4D";

    static bool metatable(const lua::index& mt, QVector4D* const)
    {
        lua::QVector4D_metatable(mt);
        return true;
    }
};

}; // namespace lua

extern "C" int luaopen_luacxx_QVector4D(lua::state* const);

#endif // LUA_CXX_QVECTOR4D_INCLUDED
