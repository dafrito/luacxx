#ifndef luacxx_QAbstractItemView_INCLUDED
#define luacxx_QAbstractItemView_INCLUDED

#include "Qt5Widgets.hpp"

class QAbstractItemView;

LUA_METATABLE_BUILT(QAbstractItemView);

extern "C" int luaopen_Qt5Widgets_QAbstractItemView(lua_State* const);

#endif // luacxx_QAbstractItemView_INCLUDED
