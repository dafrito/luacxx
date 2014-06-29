#ifndef LUA_CXX_QLINEARGRADIENT_INCLUDED
#define LUA_CXX_QLINEARGRADIENT_INCLUDED

#include "../lua-cxx/stack.hpp"

class QLinearGradient;

namespace lua {

void QLinearGradient_metatable(const lua::index& mt);

template <>
struct Metatable<QLinearGradient>
{
    static constexpr const char* name = "QLinearGradient";

    static bool metatable(const lua::index& mt, QLinearGradient* const)
    {
        lua::QLinearGradient_metatable(mt);
        return true;
    }
};

}; // namespace lua

extern "C" int luaopen_luacxx_QLinearGradient(lua_State* const);

#endif // LUA_CXX_QLINEARGRADIENT_INCLUDED
