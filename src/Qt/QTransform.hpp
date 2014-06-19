#ifndef LUA_CXX_QTRANSFORM_INCLUDED
#define LUA_CXX_QTRANSFORM_INCLUDED

#include "../stack.hpp"

class QTransform;

namespace lua {

void QTransform_metatable(const lua::index& mt);

template <>
struct Metatable<QTransform>
{
    static constexpr const char* name = "QTransform";

    static bool metatable(const lua::index& mt, QTransform* const)
    {
        lua::QTransform_metatable(mt);
        return true;
    }
};

}; // namespace lua

extern "C" int luaopen_luacxx_QTransform(lua_State* const);

#endif // LUA_CXX_QTRANSFORM_INCLUDED
