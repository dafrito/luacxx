#ifndef luacxx_QList_INCLUDED
#define luacxx_QList_INCLUDED

#include "../stack.hpp"
/*

namespace lua {

void QList_metatable(const lua::index& mt);

template <>
struct Metatable<QList>
{
    static constexpr const char* name = "QList";

    static bool metatable(const lua::index& mt, QList* const)
    {
        lua::QList_metatable(mt);
        return true;
    }
};

}; // namespace lua

extern "C" int luaopen_Qt5Core_QList(lua_State* const);
*/

#endif // luacxx_QList_INCLUDED
