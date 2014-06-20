#ifndef LUA_CXX_QPAINTER_INCLUDED
#define LUA_CXX_QPAINTER_INCLUDED

#include "../stack.hpp"
#include <QPainter>

class QPainter;

namespace lua {

void QPainter_metatable(const lua::index& mt);

template <>
struct Metatable<QPainter>
{
    static constexpr const char* name = "QPainter";

    static bool metatable(const lua::index& mt, QPainter* const)
    {
        lua::QPainter_metatable(mt);
        return true;
    }
};

template <>
struct Metatable<QPainter::CompositionMode>
{
    static constexpr const char* name = "QPainter::CompositionMode";

    static bool metatable(const lua::index& mt, const void*)
    {
        return true;
    }
};

template <>
struct Metatable<QPainter::PixmapFragmentHint>
{
    static constexpr const char* name = "QPainter::PixmapFragmentHint";

    static bool metatable(const lua::index& mt, const void*)
    {
        return true;
    }
};

template <>
struct Metatable<QPainter::RenderHint>
{
    static constexpr const char* name = "QPainter::RenderHint";

    static bool metatable(const lua::index& mt, const void*)
    {
        return true;
    }
};

}; // namespace lua

extern "C" int luaopen_luacxx_QPainter(lua_State* const);

#endif // LUA_CXX_QPAINTER_INCLUDED
