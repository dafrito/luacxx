#include "QCoreApplication.hpp"
#include "QObject.hpp"
#include "QEventLoop.hpp"

#include "../type/function.hpp"
#include "../type/numeric.hpp"
#include "../thread.hpp"

#include <QCoreApplication>

lua::QCoreApplicationArgs* lua::save_arguments(lua::index arg)
{
    auto state = arg.state();

    // Get an arguments struct, to persist the passed arguments. The size is all the arguments from
    // the given position to the end.
    auto arguments = lua::make<lua::QCoreApplicationArgs>(state, lua_gettop(state) - arg.pos() + 1);

    while (arg.pos() < lua_gettop(state)) {
        // Get the string at the given arg position
        auto value = lua::get<const char*>(arg);
        if (!value || strlen(value) == 0) {
            value = "";
        }

        // Assign it within the arguments struct, adjusting for differences in position.
        arguments->set(arg.pos() - 2, value);
        ++arg;
    }

    return arguments;
}

void lua::QCoreApplication_metatable(const lua::index& mt)
{
    lua::QObject_metatable(mt);

    mt["exec"] = &QCoreApplication::exec;
    mt["flush"] = &QCoreApplication::flush;
    mt["closingDown"] = &QCoreApplication::closingDown;
    mt["startingUp"] = &QCoreApplication::startingUp;
}

int QCoreApplication_processEvents(lua_State* const state)
{
    switch (lua_gettop(state)) {
        case 0:
            QCoreApplication::processEvents();
            break;
        case 1:
            QCoreApplication::processEvents(
                lua::get<QEventLoop::ProcessEventsFlags>(state, 1)
            );
            break;
        default:
            QCoreApplication::processEvents(
                lua::get<QEventLoop::ProcessEventsFlags>(state, 1),
                lua::get<int>(state, 2)
            );
            break;
    }
    return 0;
}

int luaopen_luacxx_QCoreApplication(lua_State* const state)
{
    luaL_requiref(state, "luacxx.QEventLoop", luaopen_luacxx_QEventLoop, false);
    lua_settop(state, 0);

    lua::thread env(state);

    env["QCoreApplication"] = lua::value::table;
    env["QCoreApplication"]["new"] = lua::QCoreApplication_new<QCoreApplication>;
    env["QCoreApplication"]["processEvents"] = QCoreApplication_processEvents;

    return 0;
}
