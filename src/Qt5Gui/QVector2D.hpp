#ifndef LUACXX_QVECTOR2D_INCLUDED
#define LUACXX_QVECTOR2D_INCLUDED

#include "../stack.hpp"

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

extern "C" int luaopen_Qt5Gui_QVector2D(lua_State* const);

#endif // LUACXX_QVECTOR2D_INCLUDED
