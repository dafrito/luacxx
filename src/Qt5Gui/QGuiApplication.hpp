#ifndef LUACXX_QGUIAPPLICATION_INCLUDED
#define LUACXX_QGUIAPPLICATION_INCLUDED

#include "Qt5Gui.hpp"

#include <QGuiApplication>

namespace lua {

void QGuiApplication_metatable(const lua::index& mt);

template <>
struct Metatable<QGuiApplication>
{
    static constexpr const char* name = "QGuiApplication";

    static bool metatable(const lua::index& mt, QGuiApplication* const)
    {
        lua::QGuiApplication_metatable(mt);
        return true;
    }
};

}; // namespace lua

extern "C" int luaopen_Qt5Gui_QGuiApplication(lua_State* const);

#endif // LUACXX_QGUIAPPLICATION_INCLUDED
