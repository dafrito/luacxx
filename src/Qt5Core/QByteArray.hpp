#ifndef luacxx_QByteArray_INCLUDED
#define luacxx_QByteArray_INCLUDED

#include "../stack.hpp"

class QByteArray;

namespace lua {

void QByteArray_metatable(const lua::index& mt);

template <>
struct Metatable<QByteArray>
{
    static constexpr const char* name = "QByteArray";

    static bool metatable(const lua::index& mt, QByteArray* const)
    {
        lua::QByteArray_metatable(mt);
        return true;
    }
};

}; // namespace lua

extern "C" int luaopen_Qt5Core_QByteArray(lua_State* const);

#endif // luacxx_QByteArray_INCLUDED
