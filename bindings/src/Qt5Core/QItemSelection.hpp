#ifndef luacxx_QItemSelection_INCLUDED
#define luacxx_QItemSelection_INCLUDED

#include "../stack.hpp"

#include <QItemSelection>

#include "QList.hpp"

// http://qt-project.org/doc/qt-5/qitemselection.html

LUA_METATABLE_INHERIT(QItemSelection, QList<QItemSelectionRange>)

extern "C" int luaopen_Qt5Core_QItemSelection(lua_State* const);

#endif // luacxx_QItemSelection_INCLUDED
