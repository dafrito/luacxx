#ifndef LUA_CXX_QICON_INCLUDED
#define LUA_CXX_QICON_INCLUDED

#include "../lua-cxx/stack.hpp"
#include <QIcon>

namespace lua {

void QIcon_metatable(const lua::index& mt);

template <>
struct Metatable<QIcon>
{
    static constexpr const char* name = "QIcon";

    static bool metatable(const lua::index& mt, QIcon* const)
    {
        lua::QIcon_metatable(mt);
        return true;
    }
};

}; // namespace lua

extern "C" int luaopen_luacxx_QIcon(lua_State* const);

#endif // LUA_CXX_QICON_INCLUDED
