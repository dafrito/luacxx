#include "QDesktopServices.hpp"
#include "../convert/callable.hpp"
#include "../thread.hpp"

#include "../Qt5Core/QUrl.hpp"
#include "../Qt5Core/QString.hpp"
#include "../Qt5Core/QObject.hpp"

int luaopen_Qt5Gui_QDesktopServices(lua_State* const state)
{
    lua::thread env(state);

    env["QDesktopServices"] = lua::value::table;
    auto t = env["QDesktopServices"];

    t["openUrl"] = QDesktopServices::openUrl;
    t["setUrlHandler"] = QDesktopServices::setUrlHandler;
    t["unsetUrlHandler"] = QDesktopServices::unsetUrlHandler;

    return 0;
}
