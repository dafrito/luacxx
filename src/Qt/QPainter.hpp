#ifndef LUA_CXX_QPAINTER_INCLUDED
#define LUA_CXX_QPAINTER_INCLUDED

#include "../stack.hpp"

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

}; // namespace lua

extern "C" int luaopen_luacxx_QPainter(lua::state* const);

#endif // LUA_CXX_QPAINTER_INCLUDED
