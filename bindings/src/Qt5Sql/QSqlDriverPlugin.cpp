#include "QSqlDriverPlugin.hpp"
#include "../convert/callable.hpp"
#include "../convert/const_char_p.hpp"
#include "../thread.hpp"

#include "../Qt5Core/QObject.hpp"

namespace lua {

void QSqlDriverPlugin_metatable(lua_State* const state, const int pos)
{
    lua::QObject_metatable(state, pos);
}

} // namespace lua
