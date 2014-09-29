#ifndef luacxx_QGraphicsTransform_INCLUDED
#define luacxx_QGraphicsTransform_INCLUDED

#include "../stack.hpp"

class QGraphicsTransform;

namespace lua {

void QGraphicsTransform_metatable(const lua::index& mt);

template <>
struct Metatable<QGraphicsTransform>
{
    static constexpr const char* name = "QGraphicsTransform";

    static bool metatable(const lua::index& mt, QGraphicsTransform* const)
    {
        lua::QGraphicsTransform_metatable(mt);
        return true;
    }
};

}; // namespace lua

extern "C" int luaopen_Qt5Widgets_QGraphicsTransform(lua_State* const);

#endif // luacxx_QGraphicsTransform_INCLUDED
