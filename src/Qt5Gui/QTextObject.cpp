#include "QTextObject.hpp"
#include "../convert/callable.hpp"
#include "../thread.hpp"

#include "QTextDocument.hpp"
#include "QTextFormat.hpp"
#include "../Qt5Core/QObject.hpp"

namespace lua {

void QTextObject_metatable(lua_State* const state, const int pos)
{
    lua::QObject_metatable(state, pos);

    lua::index mt(state, pos);
     mt["document"] = &QTextObject::document;
     mt["format"] = &QTextObject::format;
     mt["formatIndex"] = &QTextObject::formatIndex;
     mt["objectIndex"] = &QTextObject::objectIndex;
}

} // namespace lua

int luaopen_luacxx_QTextObject(lua_State* const state)
{
    lua::thread env(state);

    env["QTextObject"] = lua::value::table;

    return 0;
}
