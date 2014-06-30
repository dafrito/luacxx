#ifndef LUACXX_QRESIZEEVENT_INCLUDED
#define LUACXX_QRESIZEEVENT_INCLUDED

#include "../luacxx/stack.hpp"
#include <QResizeEvent>

namespace lua {

void QResizeEvent_metatable(const lua::index& mt);

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

}; // namespace lua

extern "C" int luaopen_Qt5Gui_QResizeEvent(lua_State* const);

#endif // LUACXX_QRESIZEEVENT_INCLUDED
