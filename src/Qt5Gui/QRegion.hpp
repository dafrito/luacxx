#ifndef LUACXX_QREGION_INCLUDED
#define LUACXX_QREGION_INCLUDED

#include "../luacxx/stack.hpp"
#include <QRegion>

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

extern "C" int luaopen_Qt5Gui_QRegion(lua_State* const);

#endif // LUACXX_QREGION_INCLUDED
