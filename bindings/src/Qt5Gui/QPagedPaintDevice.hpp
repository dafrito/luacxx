#ifndef luacxx_QPagedPaintDevice_INCLUDED
#define luacxx_QPagedPaintDevice_INCLUDED

#include "../stack.hpp"
#include "../enum.hpp"

#include <QPagedPaintDevice>

LUA_METATABLE_BUILT(QPagedPaintDevice)
LUA_METATABLE_NAMED(QPagedPaintDevice::Margins)
LUA_METATABLE_ENUM(QPagedPaintDevice::PageSize)

extern "C" int luaopen_Qt5Gui_QPagedPaintDevice(lua_State* const);

#endif // luacxx_QPagedPaintDevice_INCLUDED
