#ifndef luacxx_QLayoutItem_INCLUDED
#define luacxx_QLayoutItem_INCLUDED

#include "../stack.hpp"

class QLayoutItem;

namespace lua {

void QLayoutItem_metatable(const lua::index& mt);

template <>
struct Metatable<QLayoutItem>
{
    static constexpr const char* name = "QLayoutItem";

    static bool metatable(const lua::index& mt, QLayoutItem* const)
    {
        lua::QLayoutItem_metatable(mt);
        return true;
    }
};

}; // namespace lua

extern "C" int luaopen_Qt5Widgets_QLayoutItem(lua_State* const);

#endif // luacxx_QLayoutItem_INCLUDED
