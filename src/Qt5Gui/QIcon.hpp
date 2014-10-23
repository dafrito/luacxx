#ifndef LUACXX_QICON_INCLUDED
#define LUACXX_QICON_INCLUDED

#include "Qt5Gui.hpp"
#include "../enum.hpp"
#include <QIcon>

LUA_METATABLE_BUILT(QIcon);
LUA_METATABLE_ENUM(QIcon::Mode);
LUA_METATABLE_ENUM(QIcon::State);

extern "C" int luaopen_Qt5Gui_QIcon(lua_State* const);

#endif // LUACXX_QICON_INCLUDED
