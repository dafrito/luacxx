#ifndef luacxx_QGraphicsItemGroup_INCLUDED
#define luacxx_QGraphicsItemGroup_INCLUDED

#include "../stack.hpp"

class QGraphicsItemGroup;

namespace lua {

void QGraphicsItemGroup_metatable(const lua::index& mt);

template <>
struct Metatable<QGraphicsItemGroup>
{
    static constexpr const char* name = "QGraphicsItemGroup";

    static bool metatable(const lua::index& mt, QGraphicsItemGroup* const)
    {
        lua::QGraphicsItemGroup_metatable(mt);
        return true;
    }
};

}; // namespace lua

extern "C" int luaopen_Qt5Widgets_QGraphicsItemGroup(lua_State* const);

#endif // luacxx_QGraphicsItemGroup_INCLUDED
