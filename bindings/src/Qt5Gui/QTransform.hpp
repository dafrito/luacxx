#ifndef luacxx_QTransform_INCLUDED
#define luacxx_QTransform_INCLUDED

#include "Qt5Gui.hpp"
#include "../enum.hpp"

#include <QTransform>

LUA_METATABLE_BUILT(QTransform);
LUA_METATABLE_ENUM(QTransform::TransformationType);

extern "C" int luaopen_Qt5Gui_QTransform(lua_State* const state);

#endif // luacxx_QTransform_INCLUDED
