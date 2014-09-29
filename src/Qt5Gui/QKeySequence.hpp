#ifndef luacxx_QKeySequence_INCLUDED
#define luacxx_QKeySequence_INCLUDED

#include "Qt5Gui.hpp"

class QKeySequence;

namespace lua {

void QKeySequence_metatable(const lua::index& mt);

template <>
struct Metatable<QKeySequence>
{
    static constexpr const char* name = "QKeySequence";

    static bool metatable(const lua::index& mt, QKeySequence* const)
    {
        lua::QKeySequence_metatable(mt);
        return true;
    }
};

}; // namespace lua

extern "C" int luaopen_Qt5Gui_QKeySequence(lua_State* const);

#endif // luacxx_QKeySequence_INCLUDED
