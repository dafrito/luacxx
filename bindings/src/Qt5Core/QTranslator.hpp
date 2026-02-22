#ifndef luacxx_QTranslator_INCLUDED
#define luacxx_QTranslator_INCLUDED

#include "Qt5Core.hpp"

class QTranslator;

LUA_METATABLE_BUILT(QTranslator)

extern "C" int luaopen_Qt5Core_QTranslator(lua_State* const);

#endif // luacxx_QTranslator_INCLUDED
