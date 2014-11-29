#ifndef luacxx_QEasingCurve_INCLUDED
#define luacxx_QEasingCurve_INCLUDED

#include "../stack.hpp"
#include "../enum.hpp"

#include <QEasingCurve>

LUA_METATABLE_BUILT(QEasingCurve)
LUA_METATABLE_ENUM(QEasingCurve::Type)

extern "C" int luaopen_Qt5Core_QEasingCurve(lua_State* const);

#endif // luacxx_QEasingCurve_INCLUDED
