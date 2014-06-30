#include "gobject-introspection.hpp"
#include "Gtk/GIBaseInfo.hpp"
#include "Gtk/GIRepository.hpp"
#include "luacxx/thread.hpp"
#include "luacxx/algorithm.hpp"
#include "luacxx/type/standard.hpp"
#include "luacxx/type/function.hpp"
#include "luacxx/type/numeric.hpp"

#include <iostream>

int g_irepository_introspect(lua_State* const state)
{
    auto gi_namespace = lua::get<std::string>(state, lua_upvalueindex(1));
    lua::clear(state);

    std::stringstream str;

    int n_infos = g_irepository_get_n_infos(nullptr, gi_namespace.c_str());

    str << gi_namespace << ": namespace";
    for (int i = 0; i < n_infos; ++i) {
        GIBaseInfo* entry = g_irepository_get_info(nullptr, gi_namespace.c_str(), i);
        if (!entry) {
            continue;
        }
        const gchar* entry_name = g_base_info_get_name(entry);
        if (entry_name) {
            str << "\n\t"
                << entry_name << ": "
                << lua::GIInfoType_tostring(g_base_info_get_type(entry));
        }
        g_base_info_unref(entry);
    }

    lua::push(state, str.str());
    return lua::size(state);
}

// Create a Lua table that maps to the given namespace
int gi_import(lua_State* const state)
{
    // Get the namespace's name
    auto namespace_name = lua::get<const char*>(state, 1);
    lua_settop(state, 0);

    // and create the Lua table.
    auto table = lua::push(state, lua::value::table);
    auto mt = lua::push(state, lua::value::table);

    // Set up the index metatable
    lua::push_closure(state, [](lua_State* const state) {
        // Get arguments
        auto namespace_name = lua::get<const char*>(state, lua_upvalueindex(1));
        auto name = lua::get<const char*>(state, 2);

        // Push the entry by name (e.g. "cairo", "Surface")
        GIBaseInfo* entry = g_irepository_find_by_name(nullptr, namespace_name, name);
        if (entry) {
            lua::push(state, entry);
            lua_replace(state, 1);
            lua_settop(state, 1);
            return 1;
        }

        // Nothing found for this name, so return nothing.
        return 0;
    }, namespace_name);
    lua_setfield(state, mt.pos(), "__index");


    lua::push_closure(state, g_irepository_introspect, namespace_name);
    lua_setfield(state, mt.pos(), "__tostring");

    // Finally, hook up the metatable
    lua_setmetatable(state, table.pos());

    lua::global(state, namespace_name) = table;
    return 0;
}

// A package.seachers loader that requires a Gtk namespace.
int gi_search(lua_State* const state)
{
    // Look for the namespace by name, which should be given as the first argument (e.g. "cairo")
    auto name = lua::get<const char*>(state, 1);
    GError* err = nullptr;
    g_irepository_require(
        nullptr,
        name,
        nullptr,
        static_cast<GIRepositoryLoadFlags>(0),
        &err
    );

    if (err) {
        // Didn't find it, which is a normal condition.
        lua::push(state, err->message);
        return 1;
    }
    // Found it, so push the import function
    lua_settop(state, 0);
    lua::push(state, gi_import);
    lua::push(state, name);
    return 2;
}

// Returns a list of all Gtk-loaded namespaces.
int gi_get_loaded_namespaces(lua_State* const state)
{
    lua::clear(state);
    auto namespace_list = g_irepository_get_loaded_namespaces(nullptr);
    auto i = namespace_list;

    auto table = lua::push(state, lua::value::table);
    while (*i) {
        lua::table::insert(table, *i);
        ++i;
    }
    g_free(namespace_list);

    return 1;
}

int luaopen_luacxx_gobject_introspection(lua_State* const state)
{
    lua::table::insert(lua::global(state, "package")["searchers"], gi_search);
    return 0;
}
