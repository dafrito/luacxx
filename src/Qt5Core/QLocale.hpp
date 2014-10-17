#ifndef LUACXX_QLOCALE_INCLUDED
#define LUACXX_QLOCALE_INCLUDED

#include "Qt5Core.hpp"

#include <QLocale>

LUA_METATABLE_BUILT(QLocale)

extern "C" int luaopen_Qt5Core_QLocale(lua_State* const);

#endif // LUACXX_QLOCALE_INCLUDED
