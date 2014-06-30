#ifndef LUACXX_QOPENGLCONTEXT_INCLUDED
#define LUACXX_QOPENGLCONTEXT_INCLUDED

#include "../luacxx/stack.hpp"

class QOpenGLContext;

namespace lua {

void QOpenGLContext_metatable(const lua::index& mt);

template <>
struct Metatable<QOpenGLContext>
{
    static constexpr const char* name = "QOpenGLContext";

    static bool metatable(const lua::index& mt, QOpenGLContext* const)
    {
        lua::QOpenGLContext_metatable(mt);
        return true;
    }
};

}; // namespace lua

extern "C" int luaopen_luacxx_QOpenGLContext(lua_State* const);

#endif // LUACXX_QOPENGLCONTEXT_INCLUDED
