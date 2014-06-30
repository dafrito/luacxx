#ifndef LUACXX_QOFFSCREENSURFACE_INCLUDED
#define LUACXX_QOFFSCREENSURFACE_INCLUDED

#include "../luacxx/stack.hpp"

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

extern "C" int luaopen_Qt5Gui_QOffscreenSurface(lua_State* const);

#endif // LUACXX_QOFFSCREENSURFACE_INCLUDED
