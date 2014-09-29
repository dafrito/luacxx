#ifndef LUA_CXX_QTABBAR_INCLUDED
#define LUA_CXX_QTABBAR_INCLUDED

#include "../stack.hpp"

class QTabBar;

namespace lua {

void QTabBar_metatable(const lua::index& mt);

template <>
struct Metatable<QTabBar>
{
    static constexpr const char* name = "QTabBar";

    static bool metatable(const lua::index& mt, QTabBar* const)
    {
        lua::QTabBar_metatable(mt);
        return true;
    }
};

}; // namespace lua

extern "C" int luaopen_Qt5Widgets_QTabBar(lua_State* const);

#endif // LUA_CXX_QTABBAR_INCLUDED
