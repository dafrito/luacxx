#ifndef LUACXX_QCONICALGRADIENT_INCLUDED
#define LUACXX_QCONICALGRADIENT_INCLUDED

#include "../luacxx/stack.hpp"

class QConicalGradient;

namespace lua {

void QConicalGradient_metatable(const lua::index& mt);

template <>
struct Metatable<QConicalGradient>
{
    static constexpr const char* name = "QConicalGradient";

    static bool metatable(const lua::index& mt, QConicalGradient* const)
    {
        lua::QConicalGradient_metatable(mt);
        return true;
    }
};

}; // namespace lua

extern "C" int luaopen_luacxx_QConicalGradient(lua_State* const);

#endif // LUACXX_QCONICALGRADIENT_INCLUDED
