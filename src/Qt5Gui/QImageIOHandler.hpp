#ifndef LUA_CXX_QIMAGEIOHANDLER_INCLUDED
#define LUA_CXX_QIMAGEIOHANDLER_INCLUDED

#include "Qt5Gui.hpp"

class QImageIOHandler;

LUA_METATABLE_BUILT(QImageIOHandler);

extern "C" int luaopen_luacxx_QImageIOHandler(lua_State* const);

#endif // LUA_CXX_QIMAGEIOHANDLER_INCLUDED
