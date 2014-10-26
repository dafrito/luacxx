#ifndef luacxx_QTextFrameFormat_INCLUDED
#define luacxx_QTextFrameFormat_INCLUDED

#include "../stack.hpp"

#include <QTextFrameFormat>

LUA_METATABLE_BUILT(QTextFrameFormat)
LUA_METATABLE_ENUM(QTextFrameFormat::BorderStyle)
LUA_METATABLE_ENUM(QTextFrameFormat::Position)

extern "C" int luaopen_Qt5Gui_QTextFrameFormat(lua_State* const);

#endif // luacxx_QTextFrameFormat_INCLUDED
