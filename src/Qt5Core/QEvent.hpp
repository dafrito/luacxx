#ifndef LUACXX_QEVENT_INCLUDED
#define LUACXX_QEVENT_INCLUDED

#include "../stack.hpp"

#include <QEvent>

namespace lua {

void QEvent_metatable(const lua::index& mt, QEvent* const event);

template <>
struct Metatable<QEvent>
{
    static constexpr const char* name = "QEvent";

    static bool metatable(const lua::index& mt, QEvent* const event)
    {
        lua::QEvent_metatable(mt, event);
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
