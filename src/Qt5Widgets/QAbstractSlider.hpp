#ifndef luacxx_QAbstractSlider_INCLUDED
#define luacxx_QAbstractSlider_INCLUDED

#include "Qt5Widgets.hpp"
#include "../enum.hpp"

#include <QAbstractSlider>

LUA_METATABLE_BUILT(QAbstractSlider)
LUA_METATABLE_ENUM(QAbstractSlider::SliderAction);

extern "C" int luaopen_luacxx_QAbstractSlider(lua_State* const);

#endif // luacxx_QAbstractSlider_INCLUDED
