#ifndef luacxx_QMenu_INCLUDED
#define luacxx_QMenu_INCLUDED

#include "../stack.hpp"

class QMenu;

namespace lua {

void QMenu_metatable(const lua::index& mt);

template <>
struct Metatable<QMenu>
{
    static constexpr const char* name = "QMenu";

    static bool metatable(const lua::index& mt, QMenu* const)
    {
        lua::QMenu_metatable(mt);
        return true;
    }
};

}; // namespace lua

extern "C" int luaopen_luacxx_QMenu(lua_State* const);

#endif // luacxx_QMenu_INCLUDED
