#ifndef LUACXX_QFONT_INCLUDED
#define LUACXX_QFONT_INCLUDED

#include "Qt5Gui.hpp"
#include "../enum.hpp"
#include <QFont>

LUA_METATABLE_BUILT(QFont);
LUA_METATABLE_ENUM(QFont::Capitalization);
LUA_METATABLE_ENUM(QFont::HintingPreference);
LUA_METATABLE_ENUM(QFont::SpacingType);
LUA_METATABLE_ENUM(QFont::Stretch);
LUA_METATABLE_ENUM(QFont::Style);
LUA_METATABLE_ENUM(QFont::StyleHint);
LUA_METATABLE_ENUM(QFont::StyleStrategy);
LUA_METATABLE_ENUM(QFont::Weight);

extern "C" int luaopen_Qt5Gui_QFont(lua_State* const);

#endif // LUACXX_QFONT_INCLUDED
