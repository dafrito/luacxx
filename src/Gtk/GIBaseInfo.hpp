#ifndef LUACXX_TYPE_GIBASEINFO_INCLUDED
#define LUACXX_TYPE_GIBASEINFO_INCLUDED

#include "../luacxx/stack.hpp"
#include <girepository.h>

namespace lua {

std::string GIInfoType_tostring(GIInfoType value);
std::string GIBaseInfo_tostring(GIBaseInfo* info);
int GIBaseInfo_call(lua_State* const state);
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

#endif // LUACXX_TYPE_GIBASEINFO_INCLUDED
