#ifndef luacxx_QIconEngine_INCLUDED
#define luacxx_QIconEngine_INCLUDED

#include "Qt5Gui.hpp"
#include "../enum.hpp"

#include <QIconEngine>

LUA_METATABLE_BUILT(QIconEngine)
LUA_METATABLE_ENUM(QIconEngine::IconEngineHook)

extern "C" int luaopen_Qt5Gui_QIconEngine(lua_State* const);

#endif // luacxx_QIconEngine_INCLUDED
