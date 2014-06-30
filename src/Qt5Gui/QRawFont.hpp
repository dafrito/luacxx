#ifndef LUACXX_QRAWFONT_INCLUDED
#define LUACXX_QRAWFONT_INCLUDED

#include "../luacxx/stack.hpp"
#include <QRawFont>

namespace lua {

void QRawFont_metatable(const lua::index& mt);

template <>
struct Metatable<QRawFont>
{
    static constexpr const char* name = "QRawFont";

    static bool metatable(const lua::index& mt, QRawFont* const)
    {
        lua::QRawFont_metatable(mt);
        return true;
    }
};

}; // namespace lua

extern "C" int luaopen_Qt5Gui_QRawFont(lua_State* const);

#endif // LUACXX_QRAWFONT_INCLUDED
