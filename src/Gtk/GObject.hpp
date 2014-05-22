#ifndef LUA_CXX_GOBJECT_INCLUDED
#define LUA_CXX_GOBJECT_INCLUDED

#include "stack.hpp"

#include <glib-object.h>

namespace lua {

void GObject_metatable(const lua::index& mt);
int GObject_index(lua::state* const state);
int GObject_tostring(lua::state* const state);
int GObject_destroy(lua::state* const state);

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

#endif // LUA_CXX_GOBJECT_INCLUDED
