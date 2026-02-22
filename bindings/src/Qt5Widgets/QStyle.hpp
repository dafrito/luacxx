#ifndef LUA_CXX_QSTYLE_INCLUDED
#define LUA_CXX_QSTYLE_INCLUDED

#include "Qt5Widgets.hpp"
#include "../enum.hpp"

#include <QStyle>

LUA_METATABLE_BUILT(QStyle);
LUA_METATABLE_ENUM(QStyle::ComplexControl);
LUA_METATABLE_ENUM(QStyle::ContentsType);
LUA_METATABLE_ENUM(QStyle::ControlElement);
LUA_METATABLE_ENUM(QStyle::PixelMetric);
LUA_METATABLE_ENUM(QStyle::PrimitiveElement);
LUA_METATABLE_ENUM(QStyle::RequestSoftwareInputPanel);
LUA_METATABLE_ENUM(QStyle::StandardPixmap);
LUA_METATABLE_ENUM(QStyle::StateFlag);
LUA_METATABLE_ENUM(QStyle::StyleHint);
LUA_METATABLE_ENUM(QStyle::SubControl);
LUA_METATABLE_ENUM(QStyle::SubElement);

extern "C" int luaopen_Qt5Widgets_QStyle(lua_State* const);

#endif // LUA_CXX_QSTYLE_INCLUDED
