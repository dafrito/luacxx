#ifndef LUA_CXX_QIMAGEIOHANDLER_INCLUDED
#define LUA_CXX_QIMAGEIOHANDLER_INCLUDED

#include "Qt5Gui.hpp"
#include "../enum.hpp"

#include <QImageIOHandler>

LUA_METATABLE_BUILT(QImageIOHandler);
LUA_METATABLE_ENUM(QImageIOHandler::ImageOption);

extern "C" int luaopen_Qt5Gui_QImageIOHandler(lua_State* const);

#endif // LUA_CXX_QIMAGEIOHANDLER_INCLUDED
