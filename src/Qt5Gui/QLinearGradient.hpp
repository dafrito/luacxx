#ifndef LUACXX_QLINEARGRADIENT_INCLUDED
#define LUACXX_QLINEARGRADIENT_INCLUDED

#include "Qt5Gui.hpp"

class QLinearGradient;

namespace lua {

void QLinearGradient_metatable(const lua::index& mt);

template <>
struct Metatable<QLinearGradient>
{
    static constexpr const char* name = "QLinearGradient";

    static bool metatable(const lua::index& mt, QLinearGradient* const)
    {
        lua::QLinearGradient_metatable(mt);
        return true;
    }
};

}; // namespace lua

extern "C" int luaopen_Qt5Gui_QLinearGradient(lua_State* const);

#endif // LUACXX_QLINEARGRADIENT_INCLUDED
