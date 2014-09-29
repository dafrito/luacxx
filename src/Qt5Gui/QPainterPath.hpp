#ifndef LUACXX_QPAINTERPATH_INCLUDED
#define LUACXX_QPAINTERPATH_INCLUDED

#include "Qt5Gui.hpp"

#include <QPainterPath>

namespace lua {

void QPainterPath_metatable(const lua::index& mt);

template <>
struct Metatable<QPainterPath>
{
    static constexpr const char* name = "QPainterPath";

    static bool metatable(const lua::index& mt, QPainterPath* const)
    {
        lua::QPainterPath_metatable(mt);
        return true;
    }
};

void QPainterPath_Element_metatable(const lua::index& mt);

template <>
struct Metatable<QPainterPath::Element>
{
    static constexpr const char* name = "QPainterPath::Element";

    static bool metatable(const lua::index& mt, QPainterPath::Element* const)
    {
        lua::QPainterPath_Element_metatable(mt);
        return true;
    }
};

}; // namespace lua

extern "C" int luaopen_Qt5Gui_QPainterPath(lua_State* const);

#endif // LUACXX_QPAINTERPATH_INCLUDED
