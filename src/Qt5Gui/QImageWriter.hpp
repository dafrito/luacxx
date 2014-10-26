#ifndef LUA_CXX_QIMAGEWRITER_INCLUDED
#define LUA_CXX_QIMAGEWRITER_INCLUDED

#include "Qt5Gui.hpp"
#include "../enum.hpp"

#include <QImageWriter>

LUA_METATABLE_BUILT(QImageWriter);
LUA_METATABLE_ENUM(QImageWriter::ImageWriterError);

extern "C" int luaopen_Qt5Gui_QImageWriter(lua_State* const);

#endif // LUA_CXX_QIMAGEWRITER_INCLUDED
