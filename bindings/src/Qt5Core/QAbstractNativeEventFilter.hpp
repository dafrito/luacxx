#ifndef luacxx_QAbstractNativeEventFilter_INCLUDED
#define luacxx_QAbstractNativeEventFilter_INCLUDED

#include "Qt5Core.hpp"

class QAbstractNativeEventFilter;

LUA_METATABLE_BUILT(QAbstractNativeEventFilter);

extern "C" int luaopen_Qt5Core_QAbstractNativeEventFilter(lua_State* const);

#endif // luacxx_QAbstractNativeEventFilter_INCLUDED
