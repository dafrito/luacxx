#ifndef LUACXX_QPAINTER_INCLUDED
#define LUACXX_QPAINTER_INCLUDED

#include "Qt5Gui.hpp"
#include "../enum.hpp"
#include <QPainter>

namespace lua {
void QPainter_PixmapFragment_metatable(lua_State* const state, const int mt);
};

LUA_METATABLE_BUILT(QPainter);
LUA_METATABLE_BUILT_WITH(QPainter::PixmapFragment, QPainter_PixmapFragment_metatable);
LUA_METATABLE_ENUM(QPainter::CompositionMode);
LUA_METATABLE_ENUM(QPainter::PixmapFragmentHint);
LUA_METATABLE_ENUM(QPainter::RenderHint);

extern "C" int luaopen_Qt5Gui_QPainter(lua_State* const);

#endif // LUACXX_QPAINTER_INCLUDED
