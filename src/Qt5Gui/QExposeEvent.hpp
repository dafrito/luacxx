#ifndef LUACXX_QEXPOSEEVENT_INCLUDED
#define LUACXX_QEXPOSEEVENT_INCLUDED

#include "../luacxx/stack.hpp"

#include <QExposeEvent>

namespace lua {

void QExposeEvent_metatable(const lua::index& mt);

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

}; // namespace lua

extern "C" int luaopen_Qt5Gui_QExposeEvent(lua_State* const);

#endif // LUACXX_QEXPOSEEVENT_INCLUDED
