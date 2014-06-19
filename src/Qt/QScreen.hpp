#ifndef LUA_CXX_QSCREEN_INCLUDED
#define LUA_CXX_QSCREEN_INCLUDED

#include "../stack.hpp"

class QScreen;

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

extern "C" int luaopen_luacxx_QScreen(lua_State* const);

#endif // LUA_CXX_QSCREEN_INCLUDED
