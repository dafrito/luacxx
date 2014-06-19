#include "QMatrix.hpp"
#include "../type/function.hpp"
#include "../thread.hpp"

#include <QMatrix>

void lua::QMatrix_metatable(const lua::index& mt)
{
    // TODO Set up metatable methods for this class
}

int QMatrix_new(lua_State* const state)
{
    lua::make<QMatrix>(state);
    // TODO Set up object-specific methods

    return 1;
}

int luaopen_luacxx_QMatrix(lua_State* const state)
{
    lua::thread env(state);

    env["QMatrix"] = lua::value::table;
    env["QMatrix"]["new"] = QMatrix_new;

    return 0;
}
