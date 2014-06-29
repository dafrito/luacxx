#ifndef LUA_CXX_QFONT_INCLUDED
#define LUA_CXX_QFONT_INCLUDED

#include "../lua-cxx/stack.hpp"
#include <QFont>

namespace lua {

template <>
struct Metatable<QFont::Capitalization>
{
    static constexpr const char* name = "QFont::Capitalization";

    static bool metatable(const lua::index& mt, const void*)
    {
        return true;
    }
};

template <>
struct Metatable<QFont::HintingPreference>
{
    static constexpr const char* name = "QFont::HintingPreference";

    static bool metatable(const lua::index& mt, const void*)
    {
        return true;
    }
};

template <>
struct Metatable<QFont::SpacingType>
{
    static constexpr const char* name = "QFont::SpacingType";

    static bool metatable(const lua::index& mt, const void*)
    {
        return true;
    }
};

template <>
struct Metatable<QFont::Stretch>
{
    static constexpr const char* name = "QFont::Stretch";

    static bool metatable(const lua::index& mt, const void*)
    {
        return true;
    }
};

template <>
struct Metatable<QFont::Style>
{
    static constexpr const char* name = "QFont::Style";

    static bool metatable(const lua::index& mt, const void*)
    {
        return true;
    }
};

template <>
struct Metatable<QFont::StyleHint>
{
    static constexpr const char* name = "QFont::StyleHint";

    static bool metatable(const lua::index& mt, const void*)
    {
        return true;
    }
};

template <>
struct Metatable<QFont::StyleStrategy>
{
    static constexpr const char* name = "QFont::StyleStrategy";

    static bool metatable(const lua::index& mt, const void*)
    {
        return true;
    }
};

template <>
struct Metatable<QFont::Weight>
{
    static constexpr const char* name = "QFont::Weight";

    static bool metatable(const lua::index& mt, const void*)
    {
        return true;
    }
};

void QFont_metatable(const lua::index& mt);

template <>
struct Metatable<QFont>
{
    static constexpr const char* name = "QFont";

    static bool metatable(const lua::index& mt, QFont* const)
    {
        lua::QFont_metatable(mt);
        return true;
    }
};

}; // namespace lua

extern "C" int luaopen_luacxx_QFont(lua_State* const);

#endif // LUA_CXX_QFONT_INCLUDED
