#ifndef LUA_CXX_QIMAGEIOHANDLER_INCLUDED
#define LUA_CXX_QIMAGEIOHANDLER_INCLUDED

#include "Qt5Gui.hpp"

class QImageIOHandler;

namespace lua {

void QImageIOHandler_metatable(const lua::index& mt);

template <>
struct Metatable<QImageIOHandler>
{
    static constexpr const char* name = "QImageIOHandler";

    static bool metatable(const lua::index& mt, QImageIOHandler* const)
    {
        lua::QImageIOHandler_metatable(mt);
        return true;
    }
};

}; // namespace lua

extern "C" int luaopen_luacxx_QImageIOHandler(lua::state* const);

#endif // LUA_CXX_QIMAGEIOHANDLER_INCLUDED
