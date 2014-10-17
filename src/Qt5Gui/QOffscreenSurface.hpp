#ifndef LUACXX_QOFFSCREENSURFACE_INCLUDED
#define LUACXX_QOFFSCREENSURFACE_INCLUDED

#include "Qt5Gui.hpp"

class QOffscreenSurface;

LUA_METATABLE_BUILT(QOffscreenSurface);

extern "C" int luaopen_Qt5Gui_QOffscreenSurface(lua_State* const);

#endif // LUACXX_QOFFSCREENSURFACE_INCLUDED
