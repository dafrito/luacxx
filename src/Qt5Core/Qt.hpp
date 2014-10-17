#ifndef LUACXX_QT_INCLUDED
#define LUACXX_QT_INCLUDED

#include "Qt5Core.hpp"
#include "../global.hpp"
#include <Qt>

namespace lua {

void qt_constants_1(lua::global& t);
void qt_constants_2(lua::global& t);
void qt_constants_3(lua::global& t);
void qt_constants_4(lua::global& t);

}; // namespace lua

extern "C" int luaopen_Qt5Core_Qt(lua_State* const);

#endif // LUACXX_QT_INCLUDED
