#ifndef LUA_CXX_QOPENGLCONTEXTGROUP_INCLUDED
#define LUA_CXX_QOPENGLCONTEXTGROUP_INCLUDED

#include "../stack.hpp"

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

extern "C" int luaopen_luacxx_QOpenGLContextGroup(lua::state* const);

#endif // LUA_CXX_QOPENGLCONTEXTGROUP_INCLUDED
