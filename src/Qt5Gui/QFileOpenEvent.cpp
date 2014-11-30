#include "QFileOpenEvent.hpp"
#include "../convert/callable.hpp"
#include "../convert/const_char_p.hpp"
#include "../thread.hpp"

#include "../Qt5Core/QFlags.hpp"
#include "../Qt5Core/QUrl.hpp"
#include "../Qt5Core/QFile.hpp"
#include "../Qt5Core/QIODevice.hpp"
#include "../Qt5Core/QString.hpp"

// http://qt-project.org/doc/qt-5/qfileopenevent.html

namespace lua {

void QFileOpenEvent_metatable(lua_State* const state, const int pos)
{
    lua::index mt(state, pos);
    mt["file"] = &QFileOpenEvent::file;
    mt["openFile"] = &QFileOpenEvent::openFile;
    mt["url"] = &QFileOpenEvent::url;
}

} // namespace lua

int luaopen_Qt5Gui_QFileOpenEvent(lua_State* const state)
{
    lua::thread env(state);

    env["QFileOpenEvent"] = lua::value::table;

    return 0;
}
