#include "QTextObjectInterface.hpp"
#include "../convert/callable.hpp"
#include "../thread.hpp"

#include "QPainter.hpp"
#include "../Qt5Core/QRectF.hpp"
#include "../Qt5Core/QSizeF.hpp"
#include "QTextDocument.hpp"
#include "QTextFormat.hpp"

namespace lua {

void QTextObjectInterface_metatable(lua_State* const state, const int pos)
{
    lua::index mt(state, pos);
    mt["drawObject"] = &QTextObjectInterface::drawObject;
    mt["intrinsicSize"] = &QTextObjectInterface::intrinsicSize;
}

} // namespace lua

int luaopen_luacxx_QTextObjectInterface(lua_State* const state)
{
    lua::thread env(state);

    env["QTextObjectInterface"] = lua::value::table;

    return 0;
}
