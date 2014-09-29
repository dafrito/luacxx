#ifndef LUA_CXX_QLINEEDIT_INCLUDED
#define LUA_CXX_QLINEEDIT_INCLUDED

#include "../stack.hpp"

class QLineEdit;

namespace lua {

void QLineEdit_metatable(const lua::index& mt);

template <>
struct Metatable<QLineEdit>
{
    static constexpr const char* name = "QLineEdit";

    static bool metatable(const lua::index& mt, QLineEdit* const)
    {
        lua::QLineEdit_metatable(mt);
        return true;
    }
};

}; // namespace lua

extern "C" int luaopen_Qt5Widgets_QLineEdit(lua_State* const);

#endif // LUA_CXX_QLINEEDIT_INCLUDED
