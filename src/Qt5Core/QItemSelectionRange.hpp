#ifndef luacxx_QItemSelectionRange_INCLUDED
#define luacxx_QItemSelectionRange_INCLUDED

#include "../stack.hpp"

#include <QItemSelectionRange>

// http://qt-project.org/doc/qt-5/qitemselectionrange.html

LUA_METATABLE_BUILT(QItemSelectionRange)

extern "C" int luaopen_Qt5Core_QItemSelectionRange(lua_State* const);

#endif // luacxx_QItemSelectionRange_INCLUDED
