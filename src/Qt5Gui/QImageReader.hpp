#ifndef LUA_CXX_QIMAGEREADER_INCLUDED
#define LUA_CXX_QIMAGEREADER_INCLUDED

#include "Qt5Gui.hpp"
#include "../enum.hpp"

#include <QImageReader>

LUA_METATABLE_BUILT(QImageReader);
LUA_METATABLE_ENUM(QImageReader::ImageReaderError);

extern "C" int luaopen_luacxx_QImageReader(lua_State* const);

#endif // LUA_CXX_QIMAGEREADER_INCLUDED
