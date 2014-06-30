#ifndef LUACXX_QOPENGLFUNCTIONS_INCLUDED
#define LUACXX_QOPENGLFUNCTIONS_INCLUDED

#include "../luacxx/stack.hpp"

class QOpenGLFunctions;

namespace lua {

void QOpenGLFunctions_metatable(const lua::index& mt);

template <>
struct Metatable<QOpenGLFunctions>
{
    static constexpr const char* name = "QOpenGLFunctions";

    static bool metatable(const lua::index& mt, QOpenGLFunctions* const)
    {
        lua::QOpenGLFunctions_metatable(mt);
        return true;
    }
};

}; // namespace lua

extern "C" int luaopen_Qt5Gui_QOpenGLFunctions(lua_State* const);

#endif // LUACXX_QOPENGLFUNCTIONS_INCLUDED
