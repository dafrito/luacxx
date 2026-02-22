#ifndef luacxx_QTextObjectInterface_INCLUDED
#define luacxx_QTextObjectInterface_INCLUDED

#include "../stack.hpp"

#include <QTextObjectInterface>

LUA_METATABLE_BUILT(QTextObjectInterface)

extern "C" int luaopen_Qt5Gui_QTextObjectInterface(lua_State* const);

#endif // luacxx_QTextObjectInterface_INCLUDED
