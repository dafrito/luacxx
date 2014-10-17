#ifndef LUA_CXX_QIMAGEWRITER_INCLUDED
#define LUA_CXX_QIMAGEWRITER_INCLUDED

#include "Qt5Gui.hpp"

class QImageWriter;

LUA_METATABLE_BUILT(QImageWriter);

extern "C" int luaopen_luacxx_QImageWriter(lua_State* const);

#endif // LUA_CXX_QIMAGEWRITER_INCLUDED
