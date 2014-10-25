#ifndef luacxx_QPaintEngine_INCLUDED
#define luacxx_QPaintEngine_INCLUDED

#include "../stack.hpp"
#include "../enum.hpp"

#include <QPaintEngine>

LUA_METATABLE_BUILT(QPaintEngine);
LUA_METATABLE_ENUM(QPaintEngine::PaintEngineFeature);
LUA_METATABLE_ENUM(QPaintEngine::PolygonDrawMode);
LUA_METATABLE_ENUM(QPaintEngine::Type);
LUA_METATABLE_ENUM(QPaintEngine::DirtyFlag);

extern "C" int luaopen_Qt5Gui_QPaintEngine(lua_State* const);

#endif // luacxx_QPaintEngine_INCLUDED
