#ifndef LUACXX_QSTRINGLIST_INCLUDED
#define LUACXX_QSTRINGLIST_INCLUDED

#include "Qt5Core.hpp"
#include "QString.hpp"

#include <QStringList>

LUA_METATABLE_BUILT(QStringList)

extern "C" int luaopen_Qt5Core_QStringList(lua_State* const);

#endif // LUACXX_QSTRINGLIST_INCLUDED
