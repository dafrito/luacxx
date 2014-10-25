#include "QSocketNotifier.hpp"
#include "../convert/callable.hpp"
#include "../thread.hpp"

#include "QObject.hpp"

namespace lua {

void QSocketNotifier_metatable(lua_State* const state, const int pos)
{
    lua::QObject_metatable(state, pos);
    lua::index mt(state, pos);
    mt["isEnabled"] = &QSocketNotifier::isEnabled;
    mt["socket"] = &QSocketNotifier::socket;
    mt["type"] = &QSocketNotifier::type;
}

} // namespace lua

int QSocketNotifier_new(lua_State* const state)
{
    // QSocketNotifier(qintptr socket, Type type, QObject * parent = 0)
    lua::make<QSocketNotifier>(state,
        lua::get<qintptr>(state, 1),
        lua::get<QSocketNotifier::Type>(state, 2)
    );
    return 1;
}

int luaopen_Qt5Core_QSocketNotifier(lua_State* const state)
{
    lua::thread env(state);

    env["QSocketNotifier"] = lua::value::table;
    env["QSocketNotifier"]["new"] = QSocketNotifier_new;
    auto t = env["QSocketNotifier"];

    // enum QSocketNotifier::Type
    t["Read"] = QSocketNotifier::Read;
    t["Write"] = QSocketNotifier::Write;
    t["Exception"] = QSocketNotifier::Exception;

    return 0;
}
