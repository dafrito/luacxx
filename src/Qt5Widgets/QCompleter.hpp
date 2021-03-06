#ifndef luacxx_QCompleter_INCLUDED
#define luacxx_QCompleter_INCLUDED

#include "Qt5Widgets.hpp"
#include "../Qt5Core/QObject.hpp"
#include "../enum.hpp"

#include <QCompleter>

LUA_METATABLE_INHERIT(QCompleter, QObject);
LUA_METATABLE_ENUM(QCompleter::CompletionMode);
LUA_METATABLE_ENUM(QCompleter::ModelSorting);

extern "C" int luaopen_Qt5Widgets_QCompleter(lua_State* const);

#endif // luacxx_QCompleter_INCLUDED
