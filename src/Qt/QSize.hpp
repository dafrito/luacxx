#ifndef LUA_CXX_QSIZE_INCLUDED
#define LUA_CXX_QSIZE_INCLUDED

#include "../lua-cxx/stack.hpp"

class QSize;

namespace lua {

void QSize_metatable(const lua::index& mt);

template <>
struct Metatable<QSize>
{
    static constexpr const char* name = "QSize";

    static bool metatable(const lua::index& mt, QSize* const)
    {
        lua::QSize_metatable(mt);
        return true;
    }
};

}; // namespace lua

extern "C" int luaopen_luacxx_QSize(lua_State* const);

#endif // LUA_CXX_QSIZE_INCLUDED
