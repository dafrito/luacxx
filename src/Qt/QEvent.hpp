#ifndef LUA_CXX_QEVENT_INCLUDED
#define LUA_CXX_QEVENT_INCLUDED

#include "../lua-cxx/stack.hpp"

#include <QEvent>
#include <QResizeEvent>
#include <QExposeEvent>

namespace lua {

void QEvent_metatable(const lua::index& mt);
void QResizeEvent_metatable(const lua::index& mt);
void QExposeEvent_metatable(const lua::index& mt);

template <>
struct Metatable<QEvent>
{
    static constexpr const char* name = "QEvent";

    static bool metatable(const lua::index& mt, QEvent* const)
    {
        lua::QEvent_metatable(mt);
        return true;
    }
};

template <>
struct Metatable<QResizeEvent>
{
    static constexpr const char* name = "QResizeEvent";

    static bool metatable(const lua::index& mt, QResizeEvent* const)
    {
        lua::QResizeEvent_metatable(mt);
        return true;
    }
};

template <>
struct Metatable<QExposeEvent>
{
    static constexpr const char* name = "QExposeEvent";

    static bool metatable(const lua::index& mt, QExposeEvent* const)
    {
        lua::QExposeEvent_metatable(mt);
        return true;
    }
};

template <>
struct Push<QEvent*>
{
    static void push(lua_State* const state, QEvent* const event)
    {
        if (!event) {
            lua_pushnil(state);
            return;
        }

        switch (event->type()) {
        case QEvent::Resize:
            lua::push<QResizeEvent*>(state, static_cast<QResizeEvent*>(event));
            break;
        default:
            Construct<QEvent, lua::userdata_storage::pointer>::construct(state, event);
        }
    }
};

}; // namespace lua

extern "C" int luaopen_luacxx_QEvent(lua_State* const);

#endif // LUA_CXX_QEVENT_INCLUDED
