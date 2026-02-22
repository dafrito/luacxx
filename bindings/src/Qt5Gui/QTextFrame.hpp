#ifndef luacxx_QTextFrame_INCLUDED
#define luacxx_QTextFrame_INCLUDED

#include "../stack.hpp"

#include <QTextFrame>

#include "QTextObject.hpp"
LUA_METATABLE_INHERIT(QTextFrame, QTextObject)

extern "C" int luaopen_Qt5Gui_QTextFrame(lua_State* const);

#endif // luacxx_QTextFrame_INCLUDED
