#ifndef LUACXX_QSURFACEFORMAT_INCLUDED
#define LUACXX_QSURFACEFORMAT_INCLUDED

#include "Qt5Gui.hpp"
#include <QSurfaceFormat>

namespace lua {

void QSurfaceFormat_metatable(const lua::index& mt);

template <>
struct Metatable<QSurfaceFormat>
{
    static constexpr const char* name = "QSurfaceFormat";

    static bool metatable(const lua::index& mt, QSurfaceFormat* const)
    {
        lua::QSurfaceFormat_metatable(mt);
        return true;
    }
};

template<>
struct Push<QSurfaceFormat::FormatOptions>
{
    static void push(lua_State* const state, const QSurfaceFormat::FormatOptions& source)
    {
        lua_pushinteger(state, source);
    }
};

template<>
struct Store<QSurfaceFormat::FormatOptions>
{
    static void store(QSurfaceFormat::FormatOptions& destination, const lua::index& source)
    {
        destination = static_cast<QSurfaceFormat::FormatOptions>(
            static_cast<int>(lua_tointeger(source.state(), source.pos()))
        );
    }
};

}; // namespace lua

extern "C" int luaopen_Qt5Gui_QSurfaceFormat(lua_State* const);

#endif // LUACXX_QSURFACEFORMAT_INCLUDED
