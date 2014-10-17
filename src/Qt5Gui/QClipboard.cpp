#include "QClipboard.hpp"
#include "../convert/callable.hpp"
#include "../thread.hpp"
#include "QImage.hpp"
#include "../Qt5Core/QMimeData.hpp"
#include "QPixmap.hpp"
#include "../Qt5Core/QString.hpp"

int QClipboard_image(lua_State* const state)
{
    return 0;
}

int QClipboard_mimeData(lua_State* const state)
{
    return 0;
}

int QClipboard_pixmap(lua_State* const state)
{
    return 0;
}

int QClipboard_setImage(lua_State* const state)
{
    return 0;
}

int QClipboard_setMimeData(lua_State* const state)
{
    return 0;
}

int QClipboard_setPixmap(lua_State* const state)
{
    return 0;
}

int QClipboard_setText(lua_State* const state)
{
    return 0;
}

int QClipboard_text(lua_State* const state)
{
    return 0;
}

void lua::QClipboard_metatable(lua_State* const state, const int pos)
{
    lua::index mt(state, pos);
    mt["clear"] = &QClipboard::clear;
    mt["ownsClipboard"] = &QClipboard::ownsClipboard;
    mt["ownsFindBuffer"] = &QClipboard::ownsFindBuffer;
    mt["ownsSelection"] = &QClipboard::ownsSelection;
    mt["supportsFindBuffer"] = &QClipboard::supportsFindBuffer;
    mt["supportsSelection"] = &QClipboard::supportsSelection;

    mt["image"] = QClipboard_image;
    mt["mimeData"] = QClipboard_mimeData;
    mt["pixmap"] = QClipboard_pixmap;
    mt["setImage"] = QClipboard_setImage;
    mt["setMimeData"] = QClipboard_setMimeData;
    mt["setPixmap"] = QClipboard_setPixmap;
    mt["setText"] = QClipboard_setText;
    mt["text"] = QClipboard_text;
}

int luaopen_Qt5Gui_QClipboard(lua_State* const state)
{
    lua::thread env(state);

    env["QClipboard"] = lua::value::table;

    return 0;
}
