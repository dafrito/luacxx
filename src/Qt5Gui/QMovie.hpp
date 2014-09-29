#ifndef LUA_CXX_QMOVIE_INCLUDED
#define LUA_CXX_QMOVIE_INCLUDED

#include "Qt5Gui.hpp"

class QMovie;

namespace lua {

void QMovie_metatable(const lua::index& mt);

template <>
struct Metatable<QMovie>
{
    static constexpr const char* name = "QMovie";

    static bool metatable(const lua::index& mt, QMovie* const)
    {
        lua::QMovie_metatable(mt);
        return true;
    }
};

}; // namespace lua

extern "C" int luaopen_Qt5Gui_QMovie(lua_State* const);

#endif // LUA_CXX_QMOVIE_INCLUDED
