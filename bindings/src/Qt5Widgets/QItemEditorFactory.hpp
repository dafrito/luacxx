#ifndef luacxx_QItemEditorFactory_INCLUDED
#define luacxx_QItemEditorFactory_INCLUDED

#include "../stack.hpp"

#include <QItemEditorFactory>

// https://qt-project.org/doc/qt-5/qitemeditorfactory.html

LUA_METATABLE_BUILT(QItemEditorFactory)

extern "C" int luaopen_Qt5Widgets_QItemEditorFactory(lua_State* const);

#endif // luacxx_QItemEditorFactory_INCLUDED
