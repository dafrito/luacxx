#ifndef LUACXX_QVECTOR4D_INCLUDED
#define LUACXX_QVECTOR4D_INCLUDED

#include "../luacxx/stack.hpp"

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

extern "C" int luaopen_luacxx_QVector4D(lua_State* const);

#endif // LUACXX_QVECTOR4D_INCLUDED
