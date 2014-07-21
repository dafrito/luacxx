#ifndef LUACXX_QSIZE_INCLUDED
#define LUACXX_QSIZE_INCLUDED

#include "../stack.hpp"

class QSize;

namespace lua {

void QSize_metatable(const lua::index& mt);

template <>
struct Metatable<QSize>
{
    static constexpr const char* name = "QSize";

    static bool metatable(const lua::index& mt, QSize* const)
    {
        lua::QSize_metatable(mt);
        return true;
    }
};

}; // namespace lua

extern "C" int luaopen_Qt5Core_QSize(lua_State* const);

#endif // LUACXX_QSIZE_INCLUDED
