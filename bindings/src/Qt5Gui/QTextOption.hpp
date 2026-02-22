#ifndef LUACXX_QTEXTOPTION_INCLUDED
#define LUACXX_QTEXTOPTION_INCLUDED

#include "Qt5Gui.hpp"
#include "../enum.hpp"

#include <QTextOption>

namespace lua {
void QTextOption_Tab_metatable(lua_State* const state, const int mt);
};

LUA_METATABLE_BUILT(QTextOption);
LUA_METATABLE_BUILT_WITH(QTextOption::Tab, QTextOption_Tab_metatable);
LUA_METATABLE_ENUM(QTextOption::Flag);
LUA_METATABLE_ENUM(QTextOption::TabType);
LUA_METATABLE_ENUM(QTextOption::WrapMode);

extern "C" int luaopen_Qt5Gui_QTextOption(lua_State* const);

#endif // LUACXX_QTEXTOPTION_INCLUDED
