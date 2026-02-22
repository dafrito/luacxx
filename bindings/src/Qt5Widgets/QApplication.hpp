#ifndef luacxx_QApplication_INCLUDED
#define luacxx_QApplication_INCLUDED

#include "Qt5Widgets.hpp"

class QApplication;

LUA_METATABLE_BUILT(QApplication);

extern "C" int luaopen_Qt5Widgets_QApplication(lua_State* const);

#endif // luacxx_QApplication_INCLUDED
