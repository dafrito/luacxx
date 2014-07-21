#ifndef LUACXX_QBRUSH_INCLUDED
#define LUACXX_QBRUSH_INCLUDED

#include "../stack.hpp"

class QBrush;

namespace lua {

void QBrush_metatable(const lua::index& mt);

template <>
struct Metatable<QBrush>
{
    static constexpr const char* name = "QBrush";

    static bool metatable(const lua::index& mt, QBrush* const)
    {
        lua::QBrush_metatable(mt);
        return true;
    }
};

}; // namespace lua

extern "C" int luaopen_Qt5Gui_QBrush(lua_State* const);

#endif // LUACXX_QBRUSH_INCLUDED
