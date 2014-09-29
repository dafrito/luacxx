#ifndef luacxx_QPicture_INCLUDED
#define luacxx_QPicture_INCLUDED

#include "../stack.hpp"

class QPicture;

namespace lua {

void QPicture_metatable(const lua::index& mt);

template <>
struct Metatable<QPicture>
{
    static constexpr const char* name = "QPicture";

    static bool metatable(const lua::index& mt, QPicture* const)
    {
        lua::QPicture_metatable(mt);
        return true;
    }
};

}; // namespace lua

extern "C" int luaopen_luacxx_QPicture(lua_State* const);

#endif // luacxx_QPicture_INCLUDED
