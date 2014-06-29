#ifndef LUA_CXX_QQUATERNION_INCLUDED
#define LUA_CXX_QQUATERNION_INCLUDED

#include "../lua-cxx/stack.hpp"

class QQuaternion;

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

extern "C" int luaopen_luacxx_QQuaternion(lua_State* const);

#endif // LUA_CXX_QQUATERNION_INCLUDED
