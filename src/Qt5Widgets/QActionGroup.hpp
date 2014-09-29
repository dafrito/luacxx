#ifndef luacxx_QActionGroup_INCLUDED
#define luacxx_QActionGroup_INCLUDED

#include "../stack.hpp"

class QActionGroup;

namespace lua {

void QActionGroup_metatable(const lua::index& mt);

template <>
struct Metatable<QActionGroup>
{
    static constexpr const char* name = "QActionGroup";

    static bool metatable(const lua::index& mt, QActionGroup* const)
    {
        lua::QActionGroup_metatable(mt);
        return true;
    }
};

}; // namespace lua

extern "C" int luaopen_luacxx_QActionGroup(lua_State* const);

#endif // luacxx_QActionGroup_INCLUDED
