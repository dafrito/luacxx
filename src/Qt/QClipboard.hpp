#ifndef LUA_CXX_QCLIPBOARD_INCLUDED
#define LUA_CXX_QCLIPBOARD_INCLUDED

#include "../lua-cxx/stack.hpp"

#include <QClipboard>

namespace lua {

void QClipboard_metatable(const lua::index& mt);

template <>
struct Metatable<QClipboard>
{
    static constexpr const char* name = "QClipboard";

    static bool metatable(const lua::index& mt, QClipboard* const)
    {
        lua::QClipboard_metatable(mt);
        return true;
    }
};

}; // namespace lua

extern "C" int luaopen_luacxx_QClipboard(lua_State* const);

#endif // LUA_CXX_QCLIPBOARD_INCLUDED
