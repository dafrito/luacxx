#ifndef LUA_CXX_QSTATUSBAR_INCLUDED
#define LUA_CXX_QSTATUSBAR_INCLUDED

#include "../stack.hpp"

class QStatusBar;

namespace lua {

void QStatusBar_metatable(const lua::index& mt);

template <>
struct Metatable<QStatusBar>
{
    constexpr static const char* name = "QStatusBar";

    static bool metatable(const lua::index& mt, QStatusBar* const)
    {
        lua::QStatusBar_metatable(mt);
        return true;
    }
};

}; // namespace lua

extern "C" int luaopen_Qt5Widgets_QStatusBar(lua_State* const);

#endif // LUA_CXX_QSTATUSBAR_INCLUDED
