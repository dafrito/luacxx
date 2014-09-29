#ifndef LUA_CXX_QMENUBAR_INCLUDED
#define LUA_CXX_QMENUBAR_INCLUDED

#include "../stack.hpp"

class QMenuBar;

namespace lua {

void QMenuBar_metatable(const lua::index& mt);

template <>
struct Metatable<QMenuBar>
{
    static constexpr const char* name = "QMenuBar";

    static bool metatable(const lua::index& mt, QMenuBar* const)
    {
        lua::QMenuBar_metatable(mt);
        return true;
    }
};

}; // namespace lua

extern "C" int luaopen_Qt5Widgets_QMenuBar(lua_State* const);

#endif // LUA_CXX_QMENUBAR_INCLUDED
