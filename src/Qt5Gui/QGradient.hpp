#ifndef LUACXX_QGRADIENT_INCLUDED
#define LUACXX_QGRADIENT_INCLUDED

#include "../luacxx/stack.hpp"

class QGradient;

namespace lua {

void QGradient_metatable(const lua::index& mt);

template <>
struct Metatable<QGradient>
{
    static constexpr const char* name = "QGradient";

    static bool metatable(const lua::index& mt, QGradient* const)
    {
        lua::QGradient_metatable(mt);
        return true;
    }
};

}; // namespace lua

extern "C" int luaopen_Qt5Gui_QGradient(lua_State* const);

#endif // LUACXX_QGRADIENT_INCLUDED
