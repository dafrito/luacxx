#ifndef LUACXX_QSCREEN_INCLUDED
#define LUACXX_QSCREEN_INCLUDED

#include "Qt5Gui.hpp"
#include <QScreen>

namespace lua {

void QScreen_metatable(const lua::index& mt);

template <>
struct Metatable<QScreen>
{
    static constexpr const char* name = "QScreen";

    static bool metatable(const lua::index& mt, QScreen* const)
    {
        lua::QScreen_metatable(mt);
        return true;
    }
};

}; // namespace lua

extern "C" int luaopen_Qt5Gui_QScreen(lua_State* const);

#endif // LUACXX_QSCREEN_INCLUDED
