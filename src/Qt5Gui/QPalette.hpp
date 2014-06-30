#ifndef LUACXX_QPALETTE_INCLUDED
#define LUACXX_QPALETTE_INCLUDED

#include "../luacxx/stack.hpp"
#include <QPalette>

// http://qt-project.org/doc/qt-5/qpalette.html

namespace lua {

void QPalette_metatable(const lua::index& mt);

template <>
struct Metatable<QPalette>
{
    static constexpr const char* name = "QPalette";

    static bool metatable(const lua::index& mt, QPalette* const)
    {
        lua::QPalette_metatable(mt);
        return true;
    }
};

}; // namespace lua

extern "C" int luaopen_Qt5Gui_QPalette(lua_State* const);

#endif // LUACXX_QPALETTE_INCLUDED
