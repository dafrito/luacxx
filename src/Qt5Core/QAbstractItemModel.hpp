#ifndef luacxx_QAbstractItemModel_INCLUDED
#define luacxx_QAbstractItemModel_INCLUDED

#include "../stack.hpp"
#include "../enum.hpp"

#include <QAbstractItemModel>

#include "QObject.hpp"

// http://qt-project.org/doc/qt-5/qabstractitemmodel.html

LUA_METATABLE_INHERIT(QAbstractItemModel, QObject)
LUA_METATABLE_ENUM(QAbstractItemModel::LayoutChangeHint)

extern "C" int luaopen_Qt5Core_QAbstractItemModel(lua_State* const);

#endif // luacxx_QAbstractItemModel_INCLUDED
