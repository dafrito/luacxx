#ifndef LUA_CXX_QFRAME_INCLUDED
#define LUA_CXX_QFRAME_INCLUDED

#include "../stack.hpp"

class QFrame;

namespace lua {

void QFrame_metatable(const lua::index& mt);

template <>
struct Metatable<QFrame>
{
    static constexpr const char* name = "QFrame";

    static bool metatable(const lua::index& mt, QFrame* const)
    {
        lua::QFrame_metatable(mt);
        return true;
    }
};

}; // namespace lua

extern "C" int luaopen_Qt5Widgets_QFrame(lua_State* const);

#endif // LUA_CXX_QFRAME_INCLUDED
