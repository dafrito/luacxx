#include "QGuiApplication.hpp"
#include "QCoreApplication.hpp"
#include "QObject.hpp"
#include "QEventLoop.hpp"

#include "../type/function.hpp"
#include "../type/numeric.hpp"
#include "../thread.hpp"

#include <QGuiApplication>

void lua::QGuiApplication_metatable(const lua::index& mt)
{
    lua::QCoreApplication_metatable(mt);

    mt["exec"] = &QGuiApplication::exec;
}

int luaopen_luacxx_QGuiApplication(lua_State* const state)
{
    luaL_requiref(state, "luacxx.QEventLoop", luaopen_luacxx_QEventLoop, false);
    lua_settop(state, 0);

    lua::thread env(state);

    env["QGuiApplication"] = lua::value::table;
    env["QGuiApplication"]["new"] = lua::QCoreApplication_new<QGuiApplication>;

    return 0;
}
