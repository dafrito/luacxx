#ifndef LUACXX_QQUATERNION_INCLUDED
#define LUACXX_QQUATERNION_INCLUDED

#include "../luacxx/stack.hpp"
#include <QQuaternion>

namespace lua {

void QQuaternion_metatable(const lua::index& mt);

template <>
struct Metatable<QQuaternion>
{
    static constexpr const char* name = "QQuaternion";

    static bool metatable(const lua::index& mt, QQuaternion* const)
    {
        lua::QQuaternion_metatable(mt);
        return true;
    }
};

}; // namespace lua

extern "C" int luaopen_Qt5Gui_QQuaternion(lua_State* const);

#endif // LUACXX_QQUATERNION_INCLUDED
