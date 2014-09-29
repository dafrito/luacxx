#include "QActionGroup.hpp"
#include "../convert/callable.hpp"
#include "../thread.hpp"

#include <QActionGroup>

// http://qt-project.org/doc/qt-5/qactiongroup.html

void lua::QActionGroup_metatable(const lua::index& mt)
{
    // TODO Set up metatable methods for this class
}

int QActionGroup_new(lua_State* const state)
{
    lua::make<QActionGroup>(state, nullptr);
    // TODO Set up object-specific methods

    return 1;
}

int luaopen_luacxx_QActionGroup(lua_State* const state)
{
    lua::thread env(state);

    env["QActionGroup"] = lua::value::table;
    env["QActionGroup"]["new"] = QActionGroup_new;
    auto t = env["QActionGroup"];

    return 0;
}
