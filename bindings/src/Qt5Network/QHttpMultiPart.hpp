#ifndef luacxx_QHttpMultiPart_INCLUDED
#define luacxx_QHttpMultiPart_INCLUDED

#include "../stack.hpp"
#include "../enum.hpp"

#include <QHttpMultiPart>

#include "../Qt5Core/QObject.hpp"

// http://qt-project.org/doc/qt-5/qhttpmultipart.html

LUA_METATABLE_INHERIT(QHttpMultiPart, QObject)
LUA_METATABLE_ENUM(QHttpMultiPart::ContentType)

extern "C" int luaopen_Qt5Network_QHttpMultiPart(lua_State* const);

#endif // luacxx_QHttpMultiPart_INCLUDED
