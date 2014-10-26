#ifndef luacxx_QTextFormat_INCLUDED
#define luacxx_QTextFormat_INCLUDED

#include "../stack.hpp"
#include "../enum.hpp"

#include <QTextFormat>

LUA_METATABLE_BUILT(QTextFormat)
LUA_METATABLE_ENUM(QTextFormat::FormatType)
LUA_METATABLE_ENUM(QTextFormat::ObjectTypes)
LUA_METATABLE_ENUM(QTextFormat::PageBreakFlag)
LUA_METATABLE_ENUM(QTextFormat::Property)

extern "C" int luaopen_luacxx_QTextFormat(lua_State* const);

#endif // luacxx_QTextFormat_INCLUDED
