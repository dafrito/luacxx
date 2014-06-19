#ifndef LUA_CXX_QSET_INCLUDED
#define LUA_CXX_QSET_INCLUDED

#include "../stack.hpp"
/*

class QSet;

namespace lua {

void QSet_metatable(const lua::index& mt);

template <>
struct Metatable<QSet>
{
    static constexpr const char* name = "QSet";

    static bool metatable(const lua::index& mt, QSet* const)
    {
        lua::QSet_metatable(mt);
        return true;
    }
};

}; // namespace lua

extern "C" int luaopen_luacxx_QSet(lua_State* const);
*/

#endif // LUA_CXX_QSET_INCLUDED
