#ifndef luacxx_QCompleter_INCLUDED
#define luacxx_QCompleter_INCLUDED

#include "Qt5Widgets.hpp"

class QCompleter;

LUA_METATABLE_BUILT(QCompleter);

extern "C" int luaopen_luacxx_QCompleter(lua_State* const);

#endif // luacxx_QCompleter_INCLUDED
