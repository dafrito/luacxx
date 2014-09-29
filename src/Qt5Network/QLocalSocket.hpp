#ifndef LUA_CXX_QLOCALSOCKET_INCLUDED
#define LUA_CXX_QLOCALSOCKET_INCLUDED

#include "../stack.hpp"

class QLocalSocket;

namespace lua {

void QLocalSocket_metatable(const lua::index& mt);

template <>
struct Metatable<QLocalSocket>
{
    static constexpr const char* name = "QLocalSocket";

    static bool metatable(const lua::index& mt, QLocalSocket* const)
    {
        lua::QLocalSocket_metatable(mt);
        return true;
    }
};

}; // namespace lua

extern "C" int luaopen_luacxx_QLocalSocket(lua::state* const);

#endif // LUA_CXX_QLOCALSOCKET_INCLUDED
