#ifndef luacxx_QAbstractButton_INCLUDED
#define luacxx_QAbstractButton_INCLUDED

#include "../stack.hpp"

#include <QAbstractButton>

LUA_METATABLE_BUILT(QAbstractButton)

extern "C" int luaopen_Qt5Widgets_QAbstractButton(lua_State* const);

#endif // luacxx_QAbstractButton_INCLUDED
