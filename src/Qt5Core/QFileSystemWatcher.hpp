#ifndef luacxx_QFileSystemWatcher_INCLUDED
#define luacxx_QFileSystemWatcher_INCLUDED

#include "../stack.hpp"

#include <QFileSystemWatcher>

LUA_METATABLE_BUILT(QFileSystemWatcher)

extern "C" int luaopen_Qt5Core_QFileSystemWatcher(lua_State* const);

#endif // luacxx_QFileSystemWatcher_INCLUDED
