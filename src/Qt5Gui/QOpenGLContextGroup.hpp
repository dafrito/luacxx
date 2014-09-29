#ifndef LUACXX_QOPENGLCONTEXTGROUP_INCLUDED
#define LUACXX_QOPENGLCONTEXTGROUP_INCLUDED

#include "Qt5Gui.hpp"

class QOpenGLContextGroup;

namespace lua {

void QOpenGLContextGroup_metatable(const lua::index& mt);

template <>
struct Metatable<QOpenGLContextGroup>
{
    static constexpr const char* name = "QOpenGLContextGroup";

    static bool metatable(const lua::index& mt, QOpenGLContextGroup* const)
    {
        lua::QOpenGLContextGroup_metatable(mt);
        return true;
    }
};

}; // namespace lua

extern "C" int luaopen_Qt5Gui_QOpenGLContextGroup(lua_State* const);

#endif // LUACXX_QOPENGLCONTEXTGROUP_INCLUDED
