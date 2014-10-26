#ifndef luacxx_QTextFrame_INCLUDED
#define luacxx_QTextFrame_INCLUDED

#include "../stack.hpp"

#include <QTextFrame>

LUA_METATABLE_BUILT(QTextFrame)

extern "C" int luaopen_Qt5Gui_QTextFrame(lua_State* const);

#endif // luacxx_QTextFrame_INCLUDED
