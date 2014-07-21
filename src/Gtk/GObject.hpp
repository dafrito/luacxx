#ifndef LUACXX_GOBJECT_INCLUDED
#define LUACXX_GOBJECT_INCLUDED

#include "../stack.hpp"

#include <glib-object.h>

namespace lua {

void GObject_metatable(const lua::index& mt);
int GObject_index(lua_State* const state);
int GObject_tostring(lua_State* const state);
int GObject_destroy(lua_State* const state);

template <>
struct Metatable<GObject>
{
    static constexpr const char* name = "GObject";

    static bool metatable(const lua::index& mt, GObject* const)
    {
        lua::GObject_metatable(mt);
        return false;
    }
};

}; // namespace lua

#endif // LUACXX_GOBJECT_INCLUDED
