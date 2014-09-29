#ifndef LUA_CXX_QFONTINFO_INCLUDED
#define LUA_CXX_QFONTINFO_INCLUDED

#include "Qt5Gui.hpp"

class QFontInfo;

namespace lua {

void QFontInfo_metatable(const lua::index& mt);

template <>
struct Metatable<QFontInfo>
{
    static constexpr const char* name = "QFontInfo";

    static bool metatable(const lua::index& mt, QFontInfo* const)
    {
        lua::QFontInfo_metatable(mt);
        return true;
    }
};

}; // namespace lua

extern "C" int luaopen_luacxx_QFontInfo(lua_State* const);

#endif // LUA_CXX_QFONTINFO_INCLUDED
