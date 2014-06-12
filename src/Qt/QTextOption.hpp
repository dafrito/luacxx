#ifndef LUA_CXX_QTEXTOPTION_INCLUDED
#define LUA_CXX_QTEXTOPTION_INCLUDED

#include "../stack.hpp"

class QTextOption;

namespace lua {

void QTextOption_metatable(const lua::index& mt);

template <>
struct Metatable<QTextOption>
{
    static constexpr const char* name = "QTextOption";

    static bool metatable(const lua::index& mt, QTextOption* const)
    {
        lua::QTextOption_metatable(mt);
        return true;
    }
};

}; // namespace lua

extern "C" int luaopen_luacxx_QTextOption(lua::state* const);

#endif // LUA_CXX_QTEXTOPTION_INCLUDED
