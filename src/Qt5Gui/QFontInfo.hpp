#ifndef LUA_CXX_QFONTINFO_INCLUDED
#define LUA_CXX_QFONTINFO_INCLUDED

#include "Qt5Gui.hpp"

class QFontInfo;

LUA_METATABLE_BUILT(QFontInfo);

extern "C" int luaopen_luacxx_QFontInfo(lua_State* const);

#endif // LUA_CXX_QFONTINFO_INCLUDED
