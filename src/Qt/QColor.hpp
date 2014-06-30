#ifndef LUACXX_QCOLOR_INCLUDED
#define LUACXX_QCOLOR_INCLUDED

#include "../luacxx/stack.hpp"

class QColor;

namespace lua {

void QColor_metatable(const lua::index& mt);

template <>
struct Metatable<QColor>
{
    static constexpr const char* name = "QColor";

    static bool metatable(const lua::index& mt, QColor* const)
    {
        lua::QColor_metatable(mt);
        return true;
    }
};

}; // namespace lua

extern "C" int luaopen_luacxx_QColor(lua_State* const);

#endif // LUACXX_QCOLOR_INCLUDED
