#ifndef luacxx_QPolygonF_INCLUDED
#define luacxx_QPolygonF_INCLUDED

#include "../stack.hpp"

class QPolygonF;

namespace lua {

void QPolygonF_metatable(const lua::index& mt);

template <>
struct Metatable<QPolygonF>
{
    static constexpr const char* name = "QPolygonF";

    static bool metatable(const lua::index& mt, QPolygonF* const)
    {
        lua::QPolygonF_metatable(mt);
        return true;
    }
};

}; // namespace lua

extern "C" int luaopen_luacxx_QPolygonF(lua_State* const);

#endif // luacxx_QPolygonF_INCLUDED
