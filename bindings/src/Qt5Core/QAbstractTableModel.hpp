#ifndef luacxx_QAbstractTableModel_INCLUDED
#define luacxx_QAbstractTableModel_INCLUDED

#include "../stack.hpp"

#include <QAbstractTableModel>

#include "QAbstractItemModel.hpp"

LUA_METATABLE_INHERIT(QAbstractTableModel, QAbstractItemModel)

#endif // luacxx_QAbstractTableModel_INCLUDED
