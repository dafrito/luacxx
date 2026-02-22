#ifndef LUACXX_QSURFACEFORMAT_INCLUDED
#define LUACXX_QSURFACEFORMAT_INCLUDED

#include "Qt5Gui.hpp"
#include "../enum.hpp"

#include <QSurfaceFormat>

LUA_METATABLE_BUILT(QSurfaceFormat);
LUA_METATABLE_ENUM(QSurfaceFormat::SwapBehavior);
LUA_METATABLE_ENUM(QSurfaceFormat::RenderableType);
LUA_METATABLE_ENUM(QSurfaceFormat::OpenGLContextProfile);
LUA_METATABLE_ENUM(QSurfaceFormat::FormatOption);

extern "C" int luaopen_Qt5Gui_QSurfaceFormat(lua_State* const);

#endif // LUACXX_QSURFACEFORMAT_INCLUDED
