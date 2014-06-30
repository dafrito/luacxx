#include "GObject.hpp"
#include "GIBaseInfo.hpp"

#include "../luacxx/type/function.hpp"

#include <girepository.h>

GIBaseInfo* get_base_info(const lua::index& index)
{
    auto state = index.state();
    auto obj = lua::get<GObject*>(index);
    if (!obj) {
        return nullptr;
    }

    // Look in the metatable first for a cached value
    lua_getmetatable(state, index.pos());

    // Get the GIBaseInfo
    GIBaseInfo* base_info = nullptr;
    lua_getfield(state, -1, "GIBaseInfo");

    // Do we have a cached base info?
    if (lua_type(state, -1) != LUA_TNIL) {
        // We do, so grab it and pop everything
        base_info = lua::get<GIBaseInfo*>(state, -1);
        lua_pop(state, 2);
        return base_info;
    } else {
        lua_pop(state, 1);
    }

    // Not even a cached baseinfo, so load one
    base_info = g_irepository_find_by_gtype(nullptr,
        G_OBJECT_TYPE(obj)
    );
    if (base_info == nullptr) {
        // Nothing at all, so just bail.
        lua_pop(state, 1);
        return 0;
    }
    // Cache the base info; we also shift ownership of it to Lua
    lua::push(state, base_info);
    lua_setfield(state, -2, "GIBaseInfo");

    // Pop the metatable and return our value
    lua_pop(state, 1);
    return base_info;
}

int lua::GObject_index(lua_State* const state)
{
    // Get the object and requested name
    auto obj = lua::get<GObject*>(state, 1);
    if (!obj) {
        return 0;
    }
    auto name = lua::get<const char*>(state, 2);

    // Check for a cached value for this name
    lua_getmetatable(state, 1);
    lua_getfield(state, -1, name);
    if (lua_type(state, -1) == LUA_TNIL) {
        // No cached value, so get the base info and find the real value
        auto base_info = get_base_info(lua::index(state, 1));
        if (!base_info) {
            return 0;
        }

        switch (g_base_info_get_type(base_info)) {
        case GI_INFO_TYPE_OBJECT:
        {
            auto method = g_object_info_find_method(base_info, name);
            if (method) {
                lua::push(state, method);
                break;
            }
        }
        case GI_INFO_TYPE_INTERFACE:
        case GI_INFO_TYPE_STRUCT:
        default:
            lua::push(state, lua::value::nil);
        }
    }

    lua_replace(state, 1);
    lua_settop(state, 1);
    return 1;
}

int lua::GObject_destroy(lua_State* const state)
{
    // Unreference the object from Lua, potentially destroying it
    auto obj = lua::get<GObject*>(state, 1);
    if (obj) {
        g_object_unref(obj);
    }

    return 0;
}

int lua::GObject_tostring(lua_State* const state)
{
    GIBaseInfo* base_info = get_base_info(lua::index(state, 1));
    lua_settop(state, 0);

    if (base_info) {
        lua::push(state, lua::GIBaseInfo_tostring(base_info));
    }
    return 1;
}

void lua::GObject_metatable(const lua::index& mt)
{
    mt["__index"] = lua::GObject_index;
    mt["__tostring"] = lua::GObject_tostring;
    mt["Destroy"] = lua::GObject_destroy;
}

