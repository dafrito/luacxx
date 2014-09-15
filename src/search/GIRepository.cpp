#include "GIRepository.hpp"

#include "../Gtk/GIBaseInfo.hpp"
#include "../thread.hpp"
#include "../algorithm.hpp"
#include "../convert/string.hpp"
#include "../convert/callable.hpp"
#include "../convert/numeric.hpp"

#include <iostream>

/*

=head1 NAME

require "luacxx.search.GIRepository"

=head1 DESCRIPTION

This searcher provides automatic bindings for libraries that support GObject
introspection (e.g.  Gtk, Gdk, Pango, GStreamer). Luacxx does not attempt to
override or augment libraries loaded in this fashion, so binding quality is
dependent on the underlying library.

*/

/*

=head2 introspect_namespace(name) [lua]

Returns a string describing the specified namespace.

*/
int introspect_namespace(lua_State* const state)
{
    auto gi_namespace = lua::get<const char*>(state, 1);

    std::stringstream str;

    int n_infos = g_irepository_get_n_infos(nullptr, gi_namespace);

    str << gi_namespace << ": namespace";
    for (int i = 0; i < n_infos; ++i) {
        GIBaseInfo* entry = g_irepository_get_info(nullptr, gi_namespace, i);
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
    return 1;
}

/*

=head2 install_namespace(name) [lua]

Installs all symbols from the given namespace into the global Lua environment.

*/
int install_namespace(lua_State* const state)
{
    auto namespace_name = lua::get<const char*>(state, 1);
    auto n_infos = g_irepository_get_n_infos(nullptr, namespace_name);

    for (int i = 0; i < n_infos; ++i) {
        GIBaseInfo* const info = g_irepository_get_info(nullptr, namespace_name, i);

        auto info_type = g_base_info_get_type(info);
        auto type_name = lua::GIInfoType_tostring(info_type);

        auto install_method = [&](GIFunctionInfo* method_info) {
            lua::push(state, method_info);

            auto value_name = g_function_info_get_symbol(method_info);
            if (value_name == nullptr) {
                value_name = g_base_info_get_attribute(method_info, "c:identifier");
                if (value_name == nullptr) {
                    value_name = g_base_info_get_name(method_info);
                }
            }
            if (value_name != nullptr) {
                //std::cerr << "luacxx: Loaded " << namespace_name << " method named " << g_function_info_get_symbol(method_info) << std::endl;
                lua_setglobal(state, value_name);
            }
        };

        switch (info_type) {
        case GI_INFO_TYPE_CALLBACK:
        {
            // Callbacks are unused.
            continue;
        }
        case GI_INFO_TYPE_FUNCTION:
        {
            lua::push(state, info);
            lua_setglobal(state, g_function_info_get_symbol(info));
            //std::cerr << "luacxx: Loaded " << namespace_name << " " << type_name << " symbol named " << g_function_info_get_symbol(info) << std::endl;
            break;
        }
        case GI_INFO_TYPE_STRUCT:
        {
            for (int i = 0; i < g_struct_info_get_n_methods(info); ++i) {
                install_method(g_struct_info_get_method(info, i));
            }
            break;
        }
        case GI_INFO_TYPE_OBJECT:
        {
            for (int i = 0; i < g_object_info_get_n_methods(info); ++i) {
                install_method(g_object_info_get_method(info, i));
            }
            break;
        }
        case GI_INFO_TYPE_INTERFACE:
        {
            for (int i = 0; i < g_interface_info_get_n_methods(info); ++i) {
                install_method(g_interface_info_get_method(info, i));
            }
            break;
        }
        case GI_INFO_TYPE_FLAGS:
        case GI_INFO_TYPE_ENUM:
        {
            auto n_values = g_enum_info_get_n_values(info);

            for (int i = 0; i < n_values; ++i) {
                GIValueInfo* value_info = g_enum_info_get_value(info, i);
                if (!value_info) {
                    continue;
                }
                lua::push(state, g_value_info_get_value(value_info));

                const char* value_name = g_base_info_get_attribute(value_info, "c:identifier");
                if (value_name) {
                    //std::cerr << "luacxx: Loaded " << namespace_name << " enum value named " << value_name << std::endl;
                    lua_setglobal(state, value_name);
                } else {
                    std::cerr << "luacxx: No useful name available for "
                        << namespace_name << " enum value named" << g_base_info_get_name(info) << std::endl;
                    lua_pop(state, 1);
                }
            }

            break;
        }
        case GI_INFO_TYPE_CONSTANT:
        {
            //std::cerr << "luacxx: Loaded " << namespace_name << " constant value named " << g_base_info_get_name(info) << std::endl;

            // Get the value as a variant
            GIArgument arg;
            g_constant_info_get_value(info, &arg);

            // Get the best choice for a name
            const char* value_name = g_base_info_get_attribute(info, "c:identifier");
            if (!value_name) {
                break;
            }

            GITypeInfo* type_info = g_constant_info_get_type(info);
            auto type_tag = g_type_info_get_tag(type_info);
            switch (type_tag) {
            case GI_TYPE_TAG_INTERFACE:
            case GI_TYPE_TAG_VOID:
                lua::push(state, arg.v_pointer);
                break;
            case GI_TYPE_TAG_BOOLEAN:
                lua::push(state, arg.v_boolean);
                break;
            case GI_TYPE_TAG_INT8:
                lua::push(state, arg.v_int8);
                break;
            case GI_TYPE_TAG_UINT8:
                lua::push(state, arg.v_uint8);
                break;
            case GI_TYPE_TAG_INT16:
                lua::push(state, arg.v_int16);
                break;
            case GI_TYPE_TAG_UINT16:
                lua::push(state, arg.v_uint16);
                break;
            case GI_TYPE_TAG_INT32:
                lua::push(state, arg.v_int32);
                break;
            case GI_TYPE_TAG_UINT32:
                lua::push(state, arg.v_uint32);
                break;
            case GI_TYPE_TAG_INT64:
                lua::push(state, arg.v_int64);
                break;
            case GI_TYPE_TAG_UINT64:
                lua::push(state, arg.v_uint64);
                break;
            case GI_TYPE_TAG_FLOAT:
                lua::push(state, arg.v_float);
                break;
            case GI_TYPE_TAG_DOUBLE:
                lua::push(state, arg.v_double);
                break;
            case GI_TYPE_TAG_FILENAME:
            case GI_TYPE_TAG_UTF8:
                lua::push<const char*>(state, arg.v_string);
                break;
            case GI_TYPE_TAG_GTYPE:
            case GI_TYPE_TAG_ARRAY:
            case GI_TYPE_TAG_GLIST:
            case GI_TYPE_TAG_GSLIST:
            case GI_TYPE_TAG_GHASH:
            case GI_TYPE_TAG_ERROR:
            case GI_TYPE_TAG_UNICHAR:
            default:
            {
                std::cerr << "luacxx: No binding available for "
                    << namespace_name << " " << type_name
                    << " symbol named " << g_base_info_get_name(info) << std::endl;
                continue;
            }
            }

            lua::push(state, info);
            lua_setglobal(state, value_name);
            break;
        }
        default:
        {
            lua::push(state, info);
            lua_setglobal(state, g_base_info_get_name(info));
            std::cerr << "luacxx: No binding available for "
                << namespace_name << " " << type_name
                << " symbol named " << g_base_info_get_name(info) << std::endl;
        }
        }
    }
    return 0;
}

/*

=head2 get_loaded_namespaces() [lua]

Returns a list of all loaded namespaces.

*/
int get_loaded_namespaces(lua_State* const state)
{
    auto namespace_list = g_irepository_get_loaded_namespaces(nullptr);

    auto table = lua::push(state, lua::value::table);
    auto name = namespace_list;
    while (*name) {
        lua::table::insert(table, *name);
        ++name;
    }

    g_free(namespace_list);
    return 1;
}

/*

=head2 find_namespace(name) [lua]

Searches for the specified namespace using the GIRepository. This method is
used as a package.searchers loader whenever luacxx.search.GIRepository is
required.

*/
int find_namespace(lua_State* const state)
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
        // Didn't find it, which is a normal condition, so just return our error.
        lua::push(state, err->message);
        return 1;
    }

    // Found a namespace, so push a function to load it into the environment
    lua::push(state, install_namespace, name);
    return 2;
}

int luaopen_luacxx_search_GIRepository(lua_State* const state)
{
    lua::table::insert(lua::global(state, "package")["searchers"], find_namespace);
    return 0;
}
