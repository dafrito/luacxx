#ifndef LUA_CXX_QPAINTERPATH_INCLUDED
#define LUA_CXX_QPAINTERPATH_INCLUDED

#include "../stack.hpp"

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

extern "C" int luaopen_luacxx_QPainterPath(lua::state* const);

#endif // LUA_CXX_QPAINTERPATH_INCLUDED
