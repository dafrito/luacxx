#ifndef LUA_CXX_QBITMAP_INCLUDED
#define LUA_CXX_QBITMAP_INCLUDED

#include "../stack.hpp"

#include <QBitmap>

namespace lua {

void QBitmap_metatable(const lua::index& mt);

template <>
struct Metatable<QBitmap>
{
    static constexpr const char* name = "QBitmap";

    static bool metatable(const lua::index& mt, QBitmap* const)
    {
        lua::QBitmap_metatable(mt);
        return true;
    }
};

}; // namespace lua

extern "C" int luaopen_luacxx_QBitmap(lua_State* const);

#endif // LUA_CXX_QBITMAP_INCLUDED
