#ifndef LUACXX_QEVENT_INCLUDED
#define LUACXX_QEVENT_INCLUDED

#include "../luacxx/stack.hpp"

#include <QEvent>

namespace lua {

void QEvent_metatable(const lua::index& mt);

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

}; // namespace lua

extern "C" int luaopen_Qt5Core_QEvent(lua_State* const);

#endif // LUACXX_QEVENT_INCLUDED
