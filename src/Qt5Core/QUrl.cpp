#include "QUrl.hpp"

#include "../convert/callable.hpp"
#include "../thread.hpp"

// http://qt-project.org/doc/qt-5/qurl.html

void lua::QUrl_metatable(const lua::index& mt)
{
}

int QUrl_new(lua_State* const state)
{
    return 1;
}

int luaopen_Qt5Core_QUrl(lua_State* const state)
{
    lua::thread env(state);

    env["QUrl"] = lua::value::table;
    env["QUrl"]["new"] = QUrl_new;
    auto t = env["QUrl"];

    return 0;
}
