#ifndef LUACXX_QEVENT_INCLUDED
#define LUACXX_QEVENT_INCLUDED

#include "Qt5Core.hpp"

#include <QEvent>

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

template<>
struct Push<QEvent::Type>
{
    static void push(lua_State* const state, const QEvent::Type& source)
    {
        lua_pushinteger(state, source);
    }
};

template<>
struct Store<QEvent::Type>
{
    static void store(QEvent::Type& destination, const lua::index& source)
    {
        destination = static_cast<QEvent::Type>(lua_tointeger(source.state(), source.pos()));
    }
};

}; // namespace lua

extern "C" int luaopen_Qt5Core_QEvent(lua_State* const);

#endif // LUACXX_QEVENT_INCLUDED
