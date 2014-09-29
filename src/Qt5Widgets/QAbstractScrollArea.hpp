#ifndef LUA_CXX_QABSTRACTSCROLLAREA_INCLUDED
#define LUA_CXX_QABSTRACTSCROLLAREA_INCLUDED

#include "../stack.hpp"

class QAbstractScrollArea;

namespace lua {

void QAbstractScrollArea_metatable(const lua::index& mt);

template <>
struct Metatable<QAbstractScrollArea>
{
    static constexpr const char* name = "QAbstractScrollArea";

    static bool metatable(const lua::index& mt, QAbstractScrollArea* const)
    {
        lua::QAbstractScrollArea_metatable(mt);
        return true;
    }
};

}; // namespace lua

extern "C" int luaopen_Qt5Widgets_QAbstractScrollArea(lua_State* const);

#endif // LUA_CXX_QABSTRACTSCROLLAREA_INCLUDED
