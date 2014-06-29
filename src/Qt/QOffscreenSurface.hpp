#ifndef LUA_CXX_QOFFSCREENSURFACE_INCLUDED
#define LUA_CXX_QOFFSCREENSURFACE_INCLUDED

#include "../lua-cxx/stack.hpp"

class QOffscreenSurface;

namespace lua {

void QOffscreenSurface_metatable(const lua::index& mt);

template <>
struct Metatable<QOffscreenSurface>
{
    static constexpr const char* name = "QOffscreenSurface";

    static bool metatable(const lua::index& mt, QOffscreenSurface* const)
    {
        lua::QOffscreenSurface_metatable(mt);
        return true;
    }
};

}; // namespace lua

extern "C" int luaopen_luacxx_QOffscreenSurface(lua_State* const);

#endif // LUA_CXX_QOFFSCREENSURFACE_INCLUDED
