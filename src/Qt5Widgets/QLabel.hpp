#ifndef LUA_CXX_QLABEL_INCLUDED
#define LUA_CXX_QLABEL_INCLUDED

#include "../stack.hpp"

class QLabel;

namespace lua {

void QLabel_metatable(const lua::index& mt);

template <>
struct Metatable<QLabel>
{
    static constexpr const char* name = "QLabel";

    static bool metatable(const lua::index& mt, QLabel* const)
    {
        lua::QLabel_metatable(mt);
        return true;
    }
};

}; // namespace lua

extern "C" int luaopen_Qt5Widgets_QLabel(lua_State* const);

#endif // LUA_CXX_QLABEL_INCLUDED
