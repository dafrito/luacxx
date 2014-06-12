#ifndef LUA_CXX_QOPENGLFUNCTIONS_INCLUDED
#define LUA_CXX_QOPENGLFUNCTIONS_INCLUDED

#include "../stack.hpp"

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

extern "C" int luaopen_luacxx_QOpenGLFunctions(lua::state* const);

#endif // LUA_CXX_QOPENGLFUNCTIONS_INCLUDED
