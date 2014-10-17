#ifndef luacxx_Gtk_GIBaseInfo_INCLUDED
#define luacxx_Gtk_GIBaseInfo_INCLUDED

#include "../stack.hpp"
#include <girepository.h>

namespace lua {

std::string GIInfoType_tostring(GIInfoType value);
std::string GIBaseInfo_tostring(GIBaseInfo* info);
int GIBaseInfo_call(lua_State* const state);
void GIBaseInfo_metatable(lua_State* const state, const int mt);

template <>
struct Metatable<GIBaseInfo>
{
    static userdata_type info;

    static bool metatable(lua_State* const state, const int mt, GIBaseInfo*)
    {
        info.set_name("GIBaseInfo");
        lua::GIBaseInfo_metatable(state, mt);
        return true;
    }
};

} // namespace lua

#endif // luacxx_Gtk_GIBaseInfo_INCLUDED
