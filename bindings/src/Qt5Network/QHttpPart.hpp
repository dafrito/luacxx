#ifndef luacxx_QHttpPart_INCLUDED
#define luacxx_QHttpPart_INCLUDED

#include "../stack.hpp"

#include <QHttpPart>

// http://qt-project.org/doc/qt-5/qhttppart.html

LUA_METATABLE_BUILT(QHttpPart)

extern "C" int luaopen_Qt5Network_QHttpPart(lua_State* const);

#endif // luacxx_QHttpPart_INCLUDED
