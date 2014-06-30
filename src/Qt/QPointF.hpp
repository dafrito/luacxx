#ifndef LUACXX_QPOINTF_INCLUDED
#define LUACXX_QPOINTF_INCLUDED

#include "../luacxx/stack.hpp"

class QPointF;

namespace lua {

void QPointF_metatable(const lua::index& mt);

template <>
struct Metatable<QPointF>
{
    static constexpr const char* name = "QPointF";

    static bool metatable(const lua::index& mt, QPointF* const)
    {
        lua::QPointF_metatable(mt);
        return true;
    }
};

}; // namespace lua

extern "C" int luaopen_luacxx_QPointF(lua_State* const);

#endif // LUACXX_QPOINTF_INCLUDED
