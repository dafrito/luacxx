#ifndef LUA_CXX_QRECT_INCLUDED
#define LUA_CXX_QRECT_INCLUDED

#include "../stack.hpp"

#include <QRect>

class QRect;

namespace lua {

void QRect_metatable(const lua::index& mt);

template <>
struct Metatable<QRect>
{
    static constexpr const char* name = "QRect";

    static bool metatable(const lua::index& mt, QRect* const)
    {
        lua::QRect_metatable(mt);
        return true;
    }
};

}; // namespace lua

extern "C" int luaopen_luacxx_QRect(lua::state* const);

#endif // LUA_CXX_QRECT_INCLUDED
