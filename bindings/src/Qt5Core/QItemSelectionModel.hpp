#ifndef luacxx_QItemSelectionModel_INCLUDED
#define luacxx_QItemSelectionModel_INCLUDED

#include "../stack.hpp"
#include "../enum.hpp"

#include <QItemSelectionModel>

#include "QObject.hpp"

// http://qt-project.org/doc/qt-5/qitemselectionmodel.html

LUA_METATABLE_INHERIT(QItemSelectionModel, QObject)
LUA_METATABLE_ENUM(QItemSelectionModel::SelectionFlag)

extern "C" int luaopen_Qt5Core_QItemSelectionModel(lua_State* const);

#endif // luacxx_QItemSelectionModel_INCLUDED
