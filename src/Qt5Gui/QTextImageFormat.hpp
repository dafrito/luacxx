#ifndef luacxx_QTextImageFormat_INCLUDED
#define luacxx_QTextImageFormat_INCLUDED

#include "../stack.hpp"

#include <QTextImageFormat>

LUA_METATABLE_BUILT(QTextImageFormat)

extern "C" int luaopen_luacxx_QTextImageFormat(lua_State* const);

#endif // luacxx_QTextImageFormat_INCLUDED
