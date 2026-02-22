#ifndef luacxx_QFileSystemWatcher_INCLUDED
#define luacxx_QFileSystemWatcher_INCLUDED

#include "../stack.hpp"
#include "QObject.hpp"

#include <QFileSystemWatcher>

LUA_METATABLE_INHERIT(QFileSystemWatcher, QObject);

extern "C" int luaopen_Qt5Core_QFileSystemWatcher(lua_State* const);

#endif // luacxx_QFileSystemWatcher_INCLUDED
