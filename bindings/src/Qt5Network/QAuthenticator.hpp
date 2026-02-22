#ifndef luacxx_QAuthenticator_INCLUDED
#define luacxx_QAuthenticator_INCLUDED

#include "../stack.hpp"

#include <QAuthenticator>

// http://qt-project.org/doc/qt-5/qauthenticator.html

LUA_METATABLE_BUILT(QAuthenticator)

extern "C" int luaopen_Qt5Network_QAuthenticator(lua_State* const);

#endif // luacxx_QAuthenticator_INCLUDED
