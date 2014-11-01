#ifndef luacxx_QTextDocumentFragment_INCLUDED
#define luacxx_QTextDocumentFragment_INCLUDED

#include "../stack.hpp"

#include <QTextDocumentFragment>

LUA_METATABLE_BUILT(QTextDocumentFragment)

extern "C" int luaopen_luacxx_QTextDocumentFragment(lua_State* const);

#endif // luacxx_QTextDocumentFragment_INCLUDED
