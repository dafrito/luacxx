#ifndef LUA_CXX_QIMAGEWRITER_INCLUDED
#define LUA_CXX_QIMAGEWRITER_INCLUDED

#include "Qt5Gui.hpp"

class QImageWriter;

namespace lua {

void QImageWriter_metatable(const lua::index& mt);

template <>
struct Metatable<QImageWriter>
{
    static constexpr const char* name = "QImageWriter";

    static bool metatable(const lua::index& mt, QImageWriter* const)
    {
        lua::QImageWriter_metatable(mt);
        return true;
    }
};

}; // namespace lua

extern "C" int luaopen_luacxx_QImageWriter(lua::state* const);

#endif // LUA_CXX_QIMAGEWRITER_INCLUDED
