#ifndef luacxx_QAction_INCLUDED
#define luacxx_QAction_INCLUDED

#include "Qt5Widgets.hpp"
#include "../enum.hpp"

#include <QAction>

LUA_METATABLE_BUILT(QAction);
LUA_METATABLE_ENUM(QAction::ActionEvent);
LUA_METATABLE_ENUM(QAction::MenuRole);
LUA_METATABLE_ENUM(QAction::Priority);

#endif // luacxx_QAction_INCLUDED
