#ifndef LUA_CXX_QSTYLE_INCLUDED
#define LUA_CXX_QSTYLE_INCLUDED

#include "../stack.hpp"

class QStyle;

namespace lua {

void QStyle_metatable(const lua::index& mt);

template <>
struct Metatable<QStyle>
{
    static constexpr const char* name = "QStyle";

    static bool metatable(const lua::index& mt, QStyle* const)
    {
        lua::QStyle_metatable(mt);
        return true;
    }
};

}; // namespace lua

extern "C" int luaopen_Qt5Widgets_QStyle(lua_State* const);

#endif // LUA_CXX_QSTYLE_INCLUDED
