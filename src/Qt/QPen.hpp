#ifndef LUA_CXX_QPEN_INCLUDED
#define LUA_CXX_QPEN_INCLUDED

#include "../stack.hpp"

class QPen;

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

extern "C" int luaopen_luacxx_QPen(lua_State* const);

#endif // LUA_CXX_QPEN_INCLUDED
