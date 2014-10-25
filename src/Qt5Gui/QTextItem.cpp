#include "QTextItem.hpp"
#include "../convert/callable.hpp"
#include "../thread.hpp"

#include "QFont.hpp"
#include "../Qt5Core/QString.hpp"
#include "../Qt5Core/QFlags.hpp"

namespace lua {

void QTextItem_metatable(lua_State* const state, const int pos)
{
    lua::index mt(state, pos);
    mt["ascent"] = &QTextItem::ascent;
    mt["descent"] = &QTextItem::descent;
    mt["font"] = &QTextItem::font;
    mt["renderFlags"] = &QTextItem::renderFlags;
    mt["text"] = &QTextItem::text;
    mt["width"] = &QTextItem::width;
}

} // namespace lua

int QTextItem_new(lua_State* const state)
{
    lua::make<QTextItem>(state);
    // TODO Set up constructor

    return 1;
}

int luaopen_luacxx_QTextItem(lua_State* const state)
{
    lua::thread env(state);

    env["QTextItem"] = lua::value::table;
    env["QTextItem"]["new"] = QTextItem_new;
    auto t = env["QTextItem"];

    // enum QTextItem::RenderFlag
    t["RenderFlags"] = lua::QFlags_new<QTextItem::RenderFlags>;
    t["RightToLeft"] = QTextItem::RightToLeft;
    t["Overline"] = QTextItem::Overline;
    t["Underline"] = QTextItem::Underline;
    t["StrikeOut"] = QTextItem::StrikeOut;

    return 0;
}
