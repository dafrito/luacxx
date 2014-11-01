#include "QTextDocumentFragment.hpp"
#include "../convert/callable.hpp"
#include "../thread.hpp"

#include "../Qt5Core/QString.hpp"
#include "../Qt5Core/QByteArray.hpp"
#include "QTextDocument.hpp"
#include "QTextCursor.hpp"

int QTextDocumentFragment_toHtml(lua_State* const state)
{
    return 0;
}

namespace lua {

void QTextDocumentFragment_metatable(lua_State* const state, const int pos)
{
    lua::index mt(state, pos);
    mt["isEmpty"] = &QTextDocumentFragment::isEmpty;
    mt["toHtml"] = QTextDocumentFragment_toHtml;
    mt["toPlainText"] = &QTextDocumentFragment::toPlainText;
}

} // namespace lua

int QTextDocumentFragment_new(lua_State* const state)
{
    if (lua_gettop(state) == 0) {
        // QTextDocumentFragment()
        lua::make<QTextDocumentFragment>(state);
    } else if (lua::is_type<QTextDocument>(state, 1)) {
        // QTextDocumentFragment(const QTextDocument * document)
        lua::make<QTextDocumentFragment>(state, lua::get<QTextDocument*>(state, 1));
    } else if (lua::is_type<QTextCursor>(state, 1)) {
        // QTextDocumentFragment(const QTextCursor & cursor)
        lua::make<QTextDocumentFragment>(state, lua::get<const QTextCursor&>(state, 1));
    } else {
    // QTextDocumentFragment(const QTextDocumentFragment & other)
        lua::make<QTextDocumentFragment>(state, lua::get<const QTextDocumentFragment&>(state, 1));
    }
    return 1;
}

int static_QTextDocumentFragment_fromHtml(lua_State* const state)
{
    return 0;
}

int luaopen_luacxx_QTextDocumentFragment(lua_State* const state)
{
    lua::thread env(state);

    env["QTextDocumentFragment"] = lua::value::table;
    env["QTextDocumentFragment"]["new"] = QTextDocumentFragment_new;
    auto t = env["QTextDocumentFragment"];

    t["fromHtml"] = static_QTextDocumentFragment_fromHtml;
    t["fromPlainText"] = QTextDocumentFragment::fromPlainText;

    return 0;
}
