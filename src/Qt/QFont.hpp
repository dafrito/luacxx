#ifndef LUA_CXX_QFONT_INCLUDED
#define LUA_CXX_QFONT_INCLUDED

#include "../stack.hpp"
#include <QFont>

namespace lua {

void QFont_metatable(const lua::index& mt);

template <>
struct Metatable<QFont>
{
    static constexpr const char* name = "QFont";

    static bool metatable(const lua::index& mt, QFont* const)
    {
        lua::QFont_metatable(mt);
        return true;
    }
};

}; // namespace lua

extern "C" int luaopen_luacxx_QFont(lua_State* const);

#endif // LUA_CXX_QFONT_INCLUDED
