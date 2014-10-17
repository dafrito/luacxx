#ifndef LUACXX_QTEXTDOCUMENT_INCLUDED
#define LUACXX_QTEXTDOCUMENT_INCLUDED

#include "Qt5Gui.hpp"

class QTextDocument;

LUA_METATABLE_BUILT(QTextDocument);

extern "C" int luaopen_Qt5Gui_QTextDocument(lua_State* const);

#endif // LUACXX_QTEXTDOCUMENT_INCLUDED
