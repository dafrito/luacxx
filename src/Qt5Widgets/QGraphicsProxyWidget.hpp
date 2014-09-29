#ifndef luacxx_QGraphicsProxyWidget_INCLUDED
#define luacxx_QGraphicsProxyWidget_INCLUDED

#include "../stack.hpp"

class QGraphicsProxyWidget;

namespace lua {

void QGraphicsProxyWidget_metatable(const lua::index& mt);

template <>
struct Metatable<QGraphicsProxyWidget>
{
    static constexpr const char* name = "QGraphicsProxyWidget";

    static bool metatable(const lua::index& mt, QGraphicsProxyWidget* const)
    {
        lua::QGraphicsProxyWidget_metatable(mt);
        return true;
    }
};

}; // namespace lua

extern "C" int luaopen_Qt5Widgets_QGraphicsProxyWidget(lua_State* const);

#endif // luacxx_QGraphicsProxyWidget_INCLUDED
