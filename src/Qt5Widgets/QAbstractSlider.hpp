#ifndef luacxx_QAbstractSlider_INCLUDED
#define luacxx_QAbstractSlider_INCLUDED

#include "Qt5Widgets.hpp"
#include "../enum.hpp"
#include "QWidget.hpp"

#include <QAbstractSlider>

LUA_METATABLE_INHERIT(QAbstractSlider, QWidget);
LUA_METATABLE_ENUM(QAbstractSlider::SliderAction);

extern "C" int luaopen_Qt5Widgets_QAbstractSlider(lua_State* const);

#endif // luacxx_QAbstractSlider_INCLUDED
