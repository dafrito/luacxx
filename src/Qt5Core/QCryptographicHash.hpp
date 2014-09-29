#ifndef luacxx_QCryptographicHash_INCLUDED
#define luacxx_QCryptographicHash_INCLUDED

#include "../stack.hpp"

class QCryptographicHash;

namespace lua {

void QCryptographicHash_metatable(const lua::index& mt);

template <>
struct Metatable<QCryptographicHash>
{
    static constexpr const char* name = "QCryptographicHash";

    static bool metatable(const lua::index& mt, QCryptographicHash* const)
    {
        lua::QCryptographicHash_metatable(mt);
        return true;
    }
};

}; // namespace lua

extern "C" int luaopen_Qt5Core_QCryptographicHash(lua_State* const);

#endif // luacxx_QCryptographicHash_INCLUDED
