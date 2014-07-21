#ifndef LUACXX_QCURSOR_INCLUDED
#define LUACXX_QCURSOR_INCLUDED

#include "../stack.hpp"

class QCursor;

namespace lua {

void QCursor_metatable(const lua::index& mt);

template <>
struct Metatable<QCursor>
{
    static constexpr const char* name = "QCursor";

    static bool metatable(const lua::index& mt, QCursor* const)
    {
        lua::QCursor_metatable(mt);
        return true;
    }
};

}; // namespace lua

extern "C" int luaopen_Qt5Gui_QCursor(lua_State* const);

#endif // LUACXX_QCURSOR_INCLUDED
