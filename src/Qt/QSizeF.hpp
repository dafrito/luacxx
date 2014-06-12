#ifndef LUA_CXX_QSIZEF_INCLUDED
#define LUA_CXX_QSIZEF_INCLUDED

#include "../stack.hpp"

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

extern "C" int luaopen_luacxx_QSizeF(lua::state* const);

#endif // LUA_CXX_QSIZEF_INCLUDED
