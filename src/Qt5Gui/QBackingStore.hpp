#ifndef LUACXX_QBACKINGSTORE_INCLUDED
#define LUACXX_QBACKINGSTORE_INCLUDED

#include "Qt5Gui.hpp"

class QBackingStore;

LUA_METATABLE_BUILT(QBackingStore);

extern "C" int luaopen_Qt5Gui_QBackingStore(lua_State* const);

#endif // LUACXX_QBACKINGSTORE_INCLUDED
