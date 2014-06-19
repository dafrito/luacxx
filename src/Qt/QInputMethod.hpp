#ifndef LUA_CXX_QINPUTMETHOD_INCLUDED
#define LUA_CXX_QINPUTMETHOD_INCLUDED

#include "../stack.hpp"
#include <QInputMethod>

namespace lua {

void QInputMethod_metatable(const lua::index& mt);

template <>
struct Metatable<QInputMethod>
{
    static constexpr const char* name = "QInputMethod";

    static bool metatable(const lua::index& mt, QInputMethod* const)
    {
        lua::QInputMethod_metatable(mt);
        return true;
    }
};

}; // namespace lua

extern "C" int luaopen_luacxx_QInputMethod(lua_State* const);

#endif // LUA_CXX_QINPUTMETHOD_INCLUDED
