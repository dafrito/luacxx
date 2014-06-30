#ifndef LUACXX_QSIZEF_INCLUDED
#define LUACXX_QSIZEF_INCLUDED

#include "../luacxx/stack.hpp"

class QSizeF;

namespace lua {

void QSizeF_metatable(const lua::index& mt);

template <>
struct Metatable<QSizeF>
{
    static constexpr const char* name = "QSizeF";

    static bool metatable(const lua::index& mt, QSizeF* const)
    {
        lua::QSizeF_metatable(mt);
        return true;
    }
};

}; // namespace lua

extern "C" int luaopen_Qt5Core_QSizeF(lua_State* const);

#endif // LUACXX_QSIZEF_INCLUDED
