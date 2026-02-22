#ifndef LUACXX_GOBJECT_INCLUDED
#define LUACXX_GOBJECT_INCLUDED

#include "../stack.hpp"

#include <glib-object.h>

namespace lua {

void GObject_metatable(lua_State* const state, const int mt);
int GObject_index(lua_State* const state);
int GObject_tostring(lua_State* const state);
int GObject_destroy(lua_State* const state);

template <>
struct Metatable<GObject>
{
    static userdata_type info;

    static bool metatable(lua_State* const state, const int mt, GObject* const)
    {
        lua::GObject_metatable(state, mt);
        return false;
    }
};

}; // namespace lua

#endif // LUACXX_GOBJECT_INCLUDED
