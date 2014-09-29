#ifndef LUA_CXX_QSIZEPOLICY_INCLUDED
#define LUA_CXX_QSIZEPOLICY_INCLUDED

#include "../stack.hpp"

class QSizePolicy;

namespace lua {

void QSizePolicy_metatable(const lua::index& mt);

template <>
struct Metatable<QSizePolicy>
{
    static constexpr const char* name = "QSizePolicy";

    static bool metatable(const lua::index& mt, QSizePolicy* const)
    {
        lua::QSizePolicy_metatable(mt);
        return true;
    }
};

}; // namespace lua

extern "C" int luaopen_Qt5Widgets_QSizePolicy(lua_State* const);

#endif // LUA_CXX_QSIZEPOLICY_INCLUDED
