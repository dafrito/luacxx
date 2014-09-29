#ifndef LUACXX_QPEN_INCLUDED
#define LUACXX_QPEN_INCLUDED

#include "Qt5Gui.hpp"
#include <QPen>

namespace lua {

void QPen_metatable(const lua::index& mt);

template <>
struct Metatable<QPen>
{
    static constexpr const char* name = "QPen";

    static bool metatable(const lua::index& mt, QPen* const)
    {
        lua::QPen_metatable(mt);
        return true;
    }
};

}; // namespace lua

extern "C" int luaopen_Qt5Gui_QPen(lua_State* const);

#endif // LUACXX_QPEN_INCLUDED
