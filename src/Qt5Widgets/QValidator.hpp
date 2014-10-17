#ifndef luacxx_QValidator_INCLUDED
#define luacxx_QValidator_INCLUDED

#include "Qt5Widgets.hpp"

class QValidator;

LUA_METATABLE_BUILT(QValidator);

extern "C" int luaopen_Qt5Widgets_QValidator(lua_State* const);

#endif // luacxx_QValidator_INCLUDED
