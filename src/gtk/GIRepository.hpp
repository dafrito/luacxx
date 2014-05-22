#ifndef LUA_CXX_TYPE_GIREPOSITORY_HEADER
#define LUA_CXX_TYPE_GIREPOSITORY_HEADER

#include "stack.hpp"
#include <girepository.h>

namespace lua {

void girepository_metatable(const lua::index& mt);

template <>
struct Metatable<GIRepository>
{
    static constexpr const char* name = "GIRepository";

    static bool metatable(const lua::index& mt, GIRepository* const)
    {
        lua::girepository_metatable(mt);
        return true;
    }
};

} // namespace lua

#endif // LUA_CXX_TYPE_GIREPOSITORY_HEADER
