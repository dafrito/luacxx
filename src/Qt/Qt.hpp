#ifndef LUACXX_QT_INCLUDED
#define LUACXX_QT_INCLUDED

#include "../luacxx/stack.hpp"
#include "../luacxx/global.hpp"
#include <Qt>

namespace lua {

void qt_constants_1(lua::global& t);
void qt_constants_2(lua::global& t);
void qt_constants_3(lua::global& t);
void qt_constants_4(lua::global& t);

template <>
struct Metatable<Qt::BrushStyle>
{
    // The name for this type
    static constexpr const char* name = "Qt::BrushStyle";

    static bool metatable(const lua::index& mt, const void*)
    {
        return true;
    }
};

template <>
struct Metatable<Qt::GlobalColor>
{
    static constexpr const char* name = "Qt::GlobalColor";

    static bool metatable(const lua::index& mt, const void*)
    {
        return true;
    }
};

template <>
struct Metatable<Qt::Alignment>
{
    static constexpr const char* name = "Qt::Alignment";

    static bool metatable(const lua::index& mt, const void*)
    {
        return true;
    }
};

template <>
struct Metatable<Qt::SizeMode>
{
    static constexpr const char* name = "Qt::SizeMode";

    static bool metatable(const lua::index& mt, const void*)
    {
        return true;
    }
};

template <>
struct Metatable<Qt::FillRule>
{
    static constexpr const char* name = "Qt::FillRule";

    static bool metatable(const lua::index& mt, const void*)
    {
        return true;
    }
};

}; // namespace lua

extern "C" int luaopen_luacxx_Qt(lua_State* const);

#endif // LUACXX_QT_INCLUDED
