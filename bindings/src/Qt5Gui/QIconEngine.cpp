#include "QIconEngine.hpp"
#include "../convert/callable.hpp"
#include "../thread.hpp"

#include "QIcon.hpp"
#include "../Qt5Core/QSize.hpp"
#include "../Qt5Core/QString.hpp"
#include "../Qt5Core/QDataStream.hpp"
#include "QPixmap.hpp"
#include "../Qt5Core/QList.hpp"
#include "QPainter.hpp"
#include "../Qt5Core/QRect.hpp"

namespace lua {

void QIconEngine_metatable(lua_State* const state, const int pos)
{
    lua::index mt(state, pos);
    mt["actualSize"] = &QIconEngine::actualSize;
    mt["addFile"] = &QIconEngine::addFile;
    mt["addPixmap"] = &QIconEngine::addPixmap;
    mt["availableSizes"] = &QIconEngine::availableSizes;
    mt["clone"] = &QIconEngine::clone;
    mt["iconName"] = &QIconEngine::iconName;
    mt["key"] = &QIconEngine::key;
    mt["paint"] = &QIconEngine::paint;
    mt["pixmap"] = &QIconEngine::pixmap;
    mt["read"] = &QIconEngine::read;
    mt["virtual_hook"] = &QIconEngine::virtual_hook;
    mt["write"] = &QIconEngine::write;
}

} // namespace lua

int luaopen_Qt5Gui_QIconEngine(lua_State* const state)
{
    lua::thread env(state);

    env["QIconEngine"] = lua::value::table;
    auto t = env["QIconEngine"];

    // enum QIconEngine::IconEngineHook
    t["AvailableSizesHook"] = QIconEngine::AvailableSizesHook;
    t["IconNameHook"] = QIconEngine::IconNameHook;

    return 0;
}
