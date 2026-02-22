#ifndef LUACXX_QLOCALE_INCLUDED
#define LUACXX_QLOCALE_INCLUDED

#include "Qt5Core.hpp"
#include "../enum.hpp"

#include <QLocale>

LUA_METATABLE_BUILT(QLocale)
LUA_METATABLE_ENUM(QLocale::Country)
LUA_METATABLE_ENUM(QLocale::Language)
LUA_METATABLE_ENUM(QLocale::MeasurementSystem)
LUA_METATABLE_ENUM(QLocale::NumberOption)
LUA_METATABLE_ENUM(QLocale::Script)
LUA_METATABLE_ENUM(QLocale::FormatType)
LUA_METATABLE_ENUM(QLocale::CurrencySymbolFormat)
LUA_METATABLE_ENUM(QLocale::QuotationStyle)

extern "C" int luaopen_Qt5Core_QLocale(lua_State* const);

#endif // LUACXX_QLOCALE_INCLUDED
