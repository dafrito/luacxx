#ifndef luacxx_QAccessible_INCLUDED
#define luacxx_QAccessible_INCLUDED

#include "../stack.hpp"

#include <QAccessible>

extern "C" int luaopen_Qt5Gui_QAccessible(lua_State* const);

#endif // luacxx_QAccessible_INCLUDED
