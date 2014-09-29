#ifndef luacxx_QGraphicsLayoutItem_INCLUDED
#define luacxx_QGraphicsLayoutItem_INCLUDED

#include "../stack.hpp"

class QGraphicsLayoutItem;

namespace lua {

void QGraphicsLayoutItem_metatable(const lua::index& mt);

template <>
struct Metatable<QGraphicsLayoutItem>
{
    static constexpr const char* name = "QGraphicsLayoutItem";

    static bool metatable(const lua::index& mt, QGraphicsLayoutItem* const)
    {
        lua::QGraphicsLayoutItem_metatable(mt);
        return true;
    }
};

}; // namespace lua

extern "C" int luaopen_Qt5Widgets_QGraphicsLayoutItem(lua_State* const);

#endif // luacxx_QGraphicsLayoutItem_INCLUDED
