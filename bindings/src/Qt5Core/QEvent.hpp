#ifndef LUACXX_QEVENT_INCLUDED
#define LUACXX_QEVENT_INCLUDED

#include "Qt5Core.hpp"

#include <QEvent>
#include "../enum.hpp"

LUA_METATABLE_BUILT(QEvent);

LUA_METATABLE_ENUM(QEvent::Type);

extern "C" int luaopen_Qt5Core_QEvent(lua_State* const);

#endif // LUACXX_QEVENT_INCLUDED
