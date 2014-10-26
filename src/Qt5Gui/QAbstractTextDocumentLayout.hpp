#ifndef luacxx_QAbstractTextDocumentLayout_INCLUDED
#define luacxx_QAbstractTextDocumentLayout_INCLUDED

#include "../stack.hpp"

#include <QAbstractTextDocumentLayout>

LUA_METATABLE_BUILT(QAbstractTextDocumentLayout)
LUA_METATABLE_NAMED(QAbstractTextDocumentLayout::PaintContext)
LUA_METATABLE_NAMED(QAbstractTextDocumentLayout::Selection)

extern "C" int luaopen_Qt5Core_QAbstractTextDocumentLayout(lua_State* const);

#endif // luacxx_QAbstractTextDocumentLayout_INCLUDED
