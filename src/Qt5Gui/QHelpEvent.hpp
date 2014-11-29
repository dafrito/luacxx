#ifndef luacxx_QHelpEvent_INCLUDED
#define luacxx_QHelpEvent_INCLUDED

#include "../stack.hpp"

#include <QHelpEvent>

LUA_METATABLE_BUILT(QHelpEvent)

extern "C" int luaopen_luacxx_QHelpEvent(lua_State* const);

#endif // luacxx_QHelpEvent_INCLUDED
