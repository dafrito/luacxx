#ifndef LUA_CXX_QIMAGEREADER_INCLUDED
#define LUA_CXX_QIMAGEREADER_INCLUDED

#include "Qt5Gui.hpp"

class QImageReader;

LUA_METATABLE_BUILT(QImageReader);

extern "C" int luaopen_luacxx_QImageReader(lua_State* const);

#endif // LUA_CXX_QIMAGEREADER_INCLUDED
