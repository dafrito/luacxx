#ifndef LUA_CXX_QPALETTE_INCLUDED
#define LUA_CXX_QPALETTE_INCLUDED

#include "../lua-cxx/stack.hpp"
#include <QPalette>

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

extern "C" int luaopen_luacxx_QPalette(lua_State* const);

#endif // LUA_CXX_QPALETTE_INCLUDED
