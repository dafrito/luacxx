#ifndef luacxx_QSocketNotifier_INCLUDED
#define luacxx_QSocketNotifier_INCLUDED

#include "../stack.hpp"
#include "../enum.hpp"

#include <QSocketNotifier>

LUA_METATABLE_BUILT(QSocketNotifier)
LUA_METATABLE_ENUM(QSocketNotifier::Type);

extern "C" int luaopen_Qt5Core_QSocketNotifier(lua_State* const);

#endif // luacxx_QSocketNotifier_INCLUDED
