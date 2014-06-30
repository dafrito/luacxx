#ifndef LUACXX_QDRAG_INCLUDED
#define LUACXX_QDRAG_INCLUDED

#include "../luacxx/stack.hpp"

class QDrag;

namespace lua {

void QDrag_metatable(const lua::index& mt);

template <>
struct Metatable<QDrag>
{
    static constexpr const char* name = "QDrag";

    static bool metatable(const lua::index& mt, QDrag* const)
    {
        lua::QDrag_metatable(mt);
        return true;
    }
};

}; // namespace lua

extern "C" int luaopen_luacxx_QDrag(lua_State* const);

#endif // LUACXX_QDRAG_INCLUDED
