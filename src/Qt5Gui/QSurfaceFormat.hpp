#ifndef LUACXX_QSURFACEFORMAT_INCLUDED
#define LUACXX_QSURFACEFORMAT_INCLUDED

#include "../luacxx/stack.hpp"
#include <QSurfaceFormat>

namespace lua {

void QSurfaceFormat_metatable(const lua::index& mt);

template <>
struct Metatable<QSurfaceFormat>
{
    static constexpr const char* name = "QSurfaceFormat";

    static bool metatable(const lua::index& mt, QSurfaceFormat* const)
    {
        lua::QSurfaceFormat_metatable(mt);
        return true;
    }
};

}; // namespace lua

extern "C" int luaopen_Qt5Gui_QSurfaceFormat(lua_State* const);

#endif // LUACXX_QSURFACEFORMAT_INCLUDED
