#ifndef LUA_CXX_TYPE_GIBASEINFO_HEADER
#define LUA_CXX_TYPE_GIBASEINFO_HEADER

#include "stack.hpp"
#include <girepository.h>

namespace lua {

std::string GIInfoType_tostring(GIInfoType value);
std::string GIBaseInfo_tostring(GIBaseInfo* info);
int GIBaseInfo_call(lua::state* const state);
void GIBaseInfo_metatable(const lua::index& mt);

template <>
struct Metatable<GIBaseInfo>
{
    static constexpr const char* name = "GIBaseInfo";

    static bool metatable(const lua::index& mt, GIBaseInfo*)
    {
        lua::GIBaseInfo_metatable(mt);
        return true;
    }
};

} // namespace lua

#endif // LUA_CXX_TYPE_GIBASEINFO_HEADER
