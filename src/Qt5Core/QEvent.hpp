#ifndef LUACXX_QEVENT_INCLUDED
#define LUACXX_QEVENT_INCLUDED

#include "Qt5Core.hpp"

#include <QEvent>
#include "../enum.hpp"

namespace lua {

void QEvent_metatable(lua_State* const state, const int mt, QEvent* const value);

template <>
struct Metatable<QEvent>
{
    static const userdata_type& info()
    {
        static userdata_type _info("QEvent");
        return _info;
    }

    static bool metatable(lua_State* const state, const int mt, QEvent* const value)
    {
        lua::QEvent_metatable(state, mt, value);
        return false;
    }
};

}; // namespace lua

LUA_METATABLE_ENUM(QEvent::Type);

#ifdef HAVE_Qt5Gui
#include <QResizeEvent>
LUA_METATABLE_BUILT(QResizeEvent);

#include <QExposeEvent>
LUA_METATABLE_BUILT(QExposeEvent);
#endif

extern "C" int luaopen_Qt5Core_QEvent(lua_State* const);

#endif // LUACXX_QEVENT_INCLUDED
