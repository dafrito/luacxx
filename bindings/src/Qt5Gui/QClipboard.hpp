#ifndef LUACXX_QCLIPBOARD_INCLUDED
#define LUACXX_QCLIPBOARD_INCLUDED

#include "Qt5Gui.hpp"
#include "../enum.hpp"

#include <QClipboard>

LUA_METATABLE_BUILT(QClipboard);
LUA_METATABLE_ENUM(QClipboard::Mode);

extern "C" int luaopen_Qt5Gui_QClipboard(lua_State* const);

#endif // LUACXX_QCLIPBOARD_INCLUDED
