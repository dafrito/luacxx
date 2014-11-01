#ifndef luacxx_QTextBlockUserData_INCLUDED
#define luacxx_QTextBlockUserData_INCLUDED

#include "../stack.hpp"

#include <QTextBlockUserData>

LUA_METATABLE_BUILT(QTextBlockUserData)

extern "C" int luaopen_luacxx_QTextBlockUserData(lua_State* const);

#endif // luacxx_QTextBlockUserData_INCLUDED
