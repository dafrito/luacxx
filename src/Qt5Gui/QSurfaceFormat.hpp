#ifndef LUACXX_QSURFACEFORMAT_INCLUDED
#define LUACXX_QSURFACEFORMAT_INCLUDED

#include "Qt5Gui.hpp"
#include <QSurfaceFormat>

LUA_METATABLE_BUILT(QSurfaceFormat);

namespace lua {

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
    static void store(QSurfaceFormat::FormatOptions& destination, lua_State* const state, const int source)
    {
        destination = static_cast<QSurfaceFormat::FormatOptions>(
            static_cast<int>(lua_tointeger(state, source))
        );
    }
};

}; // namespace lua

extern "C" int luaopen_Qt5Gui_QSurfaceFormat(lua_State* const);

#endif // LUACXX_QSURFACEFORMAT_INCLUDED
