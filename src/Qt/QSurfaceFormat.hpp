#ifndef LUA_CXX_QSURFACEFORMAT_INCLUDED
#define LUA_CXX_QSURFACEFORMAT_INCLUDED

#include "../stack.hpp"

class QSurfaceFormat;

namespace lua {

void QSurfaceFormat_metatable(const lua::index& mt);

template <>
struct Metatable<QSurfaceFormat>
{
    static constexpr const char* name = "QSurfaceFormat";

    static bool metatable(const lua::index& mt, QSurfaceFormat* const)
    {
        lua::QSurfaceFormat_metatable(mt);
        return true;
    }
};

}; // namespace lua

extern "C" int luaopen_luacxx_QSurfaceFormat(lua_State* const);

#endif // LUA_CXX_QSURFACEFORMAT_INCLUDED
