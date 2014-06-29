#ifndef LUA_CXX_QFONTMETRICS_INCLUDED
#define LUA_CXX_QFONTMETRICS_INCLUDED

#include "../lua-cxx/stack.hpp"

class QFontMetrics;

namespace lua {

void QFontMetrics_metatable(const lua::index& mt);

template <>
struct Metatable<QFontMetrics>
{
    static constexpr const char* name = "QFontMetrics";

    static bool metatable(const lua::index& mt, QFontMetrics* const)
    {
        lua::QFontMetrics_metatable(mt);
        return true;
    }
};

}; // namespace lua

extern "C" int luaopen_luacxx_QFontMetrics(lua_State* const);

#endif // LUA_CXX_QFONTMETRICS_INCLUDED
