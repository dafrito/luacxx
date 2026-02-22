#ifndef luacxx_QKeySequence_INCLUDED
#define luacxx_QKeySequence_INCLUDED

#include "Qt5Gui.hpp"
#include "../enum.hpp"

#include <QKeySequence>

LUA_METATABLE_BUILT(QKeySequence);
LUA_METATABLE_ENUM(QKeySequence::SequenceFormat);
LUA_METATABLE_ENUM(QKeySequence::SequenceMatch);
LUA_METATABLE_ENUM(QKeySequence::StandardKey);

extern "C" int luaopen_Qt5Gui_QKeySequence(lua_State* const);

#endif // luacxx_QKeySequence_INCLUDED
