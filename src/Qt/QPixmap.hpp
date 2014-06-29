#ifndef LUA_CXX_QPIXMAP_INCLUDED
#define LUA_CXX_QPIXMAP_INCLUDED

#include "../lua-cxx/stack.hpp"
#include <QPixmap>

// https://qt-project.org/doc/qt-5/qpixmap.html

namespace lua {

void QPixmap_metatable(const lua::index& mt);

template <>
struct Metatable<QPixmap>
{
    static constexpr const char* name = "QPixmap";

    static bool metatable(const lua::index& mt, QPixmap* const)
    {
        lua::QPixmap_metatable(mt);
        return true;
    }
};

}; // namespace lua

extern "C" int luaopen_luacxx_QPixmap(lua_State* const);

#endif // LUA_CXX_QPIXMAP_INCLUDED
