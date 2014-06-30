#include "QInputMethod.hpp"
#include "../luacxx/type/function.hpp"
#include "../luacxx/thread.hpp"

#include <QInputMethod>

void lua::QInputMethod_metatable(const lua::index& mt)
{
    // TODO Set up metatable methods for this class
}

int luaopen_luacxx_QInputMethod(lua_State* const state)
{
    lua::thread env(state);

    env["QInputMethod"] = lua::value::table;

    return 0;
}
