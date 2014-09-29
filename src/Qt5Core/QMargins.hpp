#ifndef LUA_CXX_QMARGINS_INCLUDED
#define LUA_CXX_QMARGINS_INCLUDED

#include "../stack.hpp"

class QMargins;

namespace lua {

void QMargins_metatable(const lua::index& mt);

template <>
struct Metatable<QMargins>
{
    static constexpr const char* name = "QMargins";

    static bool metatable(const lua::index& mt, QMargins* const)
    {
        lua::QMargins_metatable(mt);
        return true;
    }
};

}; // namespace lua

extern "C" int luaopen_luacxx_QMargins(lua_State* const);

#endif // LUA_CXX_QMARGINS_INCLUDED
