#ifndef LUA_CXX_QIMAGEREADER_INCLUDED
#define LUA_CXX_QIMAGEREADER_INCLUDED

#include "Qt5Gui.hpp"

class QImageReader;

namespace lua {

void QImageReader_metatable(const lua::index& mt);

template <>
struct Metatable<QImageReader>
{
    static constexpr const char* name = "QImageReader";

    static bool metatable(const lua::index& mt, QImageReader* const)
    {
        lua::QImageReader_metatable(mt);
        return true;
    }
};

}; // namespace lua

extern "C" int luaopen_luacxx_QImageReader(lua::state* const);

#endif // LUA_CXX_QIMAGEREADER_INCLUDED
