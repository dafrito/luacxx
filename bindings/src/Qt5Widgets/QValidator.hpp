#ifndef luacxx_QValidator_INCLUDED
#define luacxx_QValidator_INCLUDED

#include "Qt5Widgets.hpp"
#include "../enum.hpp"

#include <QValidator>

LUA_METATABLE_BUILT(QValidator);
LUA_METATABLE_ENUM(QValidator::State);

extern "C" int luaopen_Qt5Widgets_QValidator(lua_State* const);

#endif // luacxx_QValidator_INCLUDED
