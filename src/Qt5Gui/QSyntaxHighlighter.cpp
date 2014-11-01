#include "QSyntaxHighlighter.hpp"
#include "../convert/callable.hpp"
#include "../convert/const_char_p.hpp"
#include "../thread.hpp"

#include "../Qt5Core/QObject.hpp"
#include "QTextDocument.hpp"

namespace lua {

void QSyntaxHighlighter_metatable(lua_State* const state, const int pos)
{
    lua::QObject_metatable(state, pos);

    lua::index mt(state, pos);
    mt["document"] = &QSyntaxHighlighter::document;
    mt["setDocument"] = &QSyntaxHighlighter::setDocument;
}

} // namespace lua

int luaopen_Qt5Gui_QSyntaxHighlighter(lua_State* const state)
{
    lua::thread env(state);

    env["QSyntaxHighlighter"] = lua::value::table;
    auto t = env["QSyntaxHighlighter"];

    return 0;
}
