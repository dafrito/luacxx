#ifndef LUA_CXX_QLOCALE_INCLUDED
#define LUA_CXX_QLOCALE_INCLUDED

#include "../stack.hpp"

class QLocale;

namespace lua {

void QLocale_metatable(const lua::index& mt);

template <>
struct Metatable<QLocale>
{
    static constexpr const char* name = "QLocale";

    static bool metatable(const lua::index& mt, QLocale* const)
    {
        lua::QLocale_metatable(mt);
        return true;
    }
};

}; // namespace lua

extern "C" int luaopen_luacxx_QLocale(lua_State* const);

#endif // LUA_CXX_QLOCALE_INCLUDED
