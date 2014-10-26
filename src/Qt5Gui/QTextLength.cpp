#include "QTextLength.hpp"
#include "../convert/callable.hpp"
#include "../thread.hpp"

namespace lua {

void QTextLength_metatable(lua_State* const state, const int pos)
{
    lua::index mt(state, pos);
    mt["rawValue"] = &QTextLength::rawValue;
    mt["type"] = &QTextLength::type;
    mt["value"] = &QTextLength::value;
}

} // namespace lua

int QTextLength_new(lua_State* const state)
{
    if (lua_gettop(state) > 0) {
        // QTextLength(Type type, qreal value)
        lua::make<QTextLength>(state,
            lua::get<QTextLength::Type>(state, 1),
            lua::get<qreal>(state, 2)
        );
    } else {
        // QTextLength()
        lua::make<QTextLength>(state);
    }
    return 1;
}

int luaopen_luacxx_QTextLength(lua_State* const state)
{
    lua::thread env(state);

    env["QTextLength"] = lua::value::table;
    env["QTextLength"]["new"] = QTextLength_new;
    auto t = env["QTextLength"];

    // enum QTextLength::Type
    t["VariableLength"] = QTextLength::VariableLength;
    t["FixedLength"] = QTextLength::FixedLength;
    t["PercentageLength"] = QTextLength::PercentageLength;

    return 0;
}
