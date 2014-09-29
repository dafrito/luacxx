#ifndef luacxx_QLayout_INCLUDED
#define luacxx_QLayout_INCLUDED

#include "../stack.hpp"

class QLayout;

namespace lua {

void QLayout_metatable(const lua::index& mt);

template <>
struct Metatable<QLayout>
{
    static constexpr const char* name = "QLayout";

    static bool metatable(const lua::index& mt, QLayout* const)
    {
        lua::QLayout_metatable(mt);
        return true;
    }
};

}; // namespace lua

extern "C" int luaopen_Qt5Widgets_QLayout(lua_State* const);

#endif // luacxx_QLayout_INCLUDED
