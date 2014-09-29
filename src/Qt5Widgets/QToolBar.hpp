#ifndef luacxx_QToolBar_INCLUDED
#define luacxx_QToolBar_INCLUDED

#include "../stack.hpp"

class QToolBar;

namespace lua {

void QToolBar_metatable(const lua::index& mt);

template <>
struct Metatable<QToolBar>
{
    static constexpr const char* name = "QToolBar";

    static bool metatable(const lua::index& mt, QToolBar* const)
    {
        lua::QToolBar_metatable(mt);
        return true;
    }
};

}; // namespace lua

extern "C" int luaopen_luacxx_QToolBar(lua_State* const);

#endif // luacxx_QToolBar_INCLUDED
