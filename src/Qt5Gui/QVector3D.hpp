#ifndef LUACXX_QVECTOR3D_INCLUDED
#define LUACXX_QVECTOR3D_INCLUDED

#include "../stack.hpp"

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

extern "C" int luaopen_Qt5Gui_QVector3D(lua_State* const);

#endif // LUACXX_QVECTOR3D_INCLUDED
