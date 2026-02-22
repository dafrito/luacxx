#ifndef luacxx_QHostInfo_INCLUDED
#define luacxx_QHostInfo_INCLUDED

#include "../stack.hpp"
#include "../enum.hpp"

#include <QHostInfo>

// http://qt-project.org/doc/qt-5/qhostinfo.html

LUA_METATABLE_BUILT(QHostInfo)
LUA_METATABLE_ENUM(QHostInfo::HostInfoError)

extern "C" int luaopen_Qt5Network_QHostInfo(lua_State* const);

#endif // luacxx_QHostInfo_INCLUDED
