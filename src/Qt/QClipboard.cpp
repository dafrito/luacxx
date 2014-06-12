#include "QClipboard.hpp"
#include "../type/function.hpp"
#include "../thread.hpp"
#include "QImage.hpp"
#include "QMimeData.hpp"
#include "QPixmap.hpp"
#include "QString.hpp"

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

void lua::QClipboard_metatable(const lua::index& mt)
{
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

int luaopen_luacxx_QClipboard(lua::state* const state)
{
    lua::thread env(state);

    env["QClipboard"] = lua::value::table;

    return 0;
}
