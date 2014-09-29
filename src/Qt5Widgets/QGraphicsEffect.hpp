#ifndef luacxx_QGraphicsEffect_INCLUDED
#define luacxx_QGraphicsEffect_INCLUDED

#include "../stack.hpp"

class QGraphicsEffect;

namespace lua {

void QGraphicsEffect_metatable(const lua::index& mt);

template <>
struct Metatable<QGraphicsEffect>
{
    static constexpr const char* name = "QGraphicsEffect";

    static bool metatable(const lua::index& mt, QGraphicsEffect* const)
    {
        lua::QGraphicsEffect_metatable(mt);
        return true;
    }
};

}; // namespace lua

extern "C" int luaopen_Qt5Widgets_QGraphicsEffect(lua_State* const);

#endif // luacxx_QGraphicsEffect_INCLUDED
