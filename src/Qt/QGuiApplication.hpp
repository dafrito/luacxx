#ifndef LUA_CXX_QGUIAPPLICATION_INCLUDED
#define LUA_CXX_QGUIAPPLICATION_INCLUDED

#include "../stack.hpp"

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

extern "C" int luaopen_luacxx_QGuiApplication(lua_State* const);

#endif // LUA_CXX_QGUIAPPLICATION_INCLUDED
