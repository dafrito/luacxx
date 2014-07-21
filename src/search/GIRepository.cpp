#include "GIRepository.hpp"

#include "../Gtk/GIBaseInfo.hpp"
#include "../thread.hpp"
#include "../algorithm.hpp"
#include "../convert/string.hpp"
#include "../convert/callable.hpp"
#include "../convert/numeric.hpp"

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

void
print_attributes (GIBaseInfo *info)
{
  GIAttributeIter iter = { 0, };
  char *name;
  char *value;
  while (g_base_info_iterate_attributes (info, &iter, &name, &value))
    {
      g_print ("attribute name: %s value: %s", name, value);
    }
}

// gi_import(namespace_name);
int gi_import(lua_State* const state)
{
    auto namespace_name = lua::get<const char*>(state, 1);
    auto n_infos = g_irepository_get_n_infos(nullptr, namespace_name);

    for (int i = 0; i < n_infos; ++i) {
        GIBaseInfo* const info = g_irepository_get_info(nullptr, namespace_name, i);
        lua::push(state, info);

        auto info_type = g_base_info_get_type(info);
        auto type_name = lua::GIInfoType_tostring(info_type);

        switch (info_type) {
        case GI_INFO_TYPE_FUNCTION:
        {
            lua_setglobal(state, g_function_info_get_symbol(info));
            std::cerr << "luacxx: Loaded " << namespace_name << " " << type_name << " symbol named " << g_function_info_get_symbol(info) << std::endl;
            break;
        }
        case GI_INFO_TYPE_STRUCT:
        {
            for (int i = 0; i < g_struct_info_get_n_methods(info); ++i) {
                GIFunctionInfo* method_info = g_struct_info_get_method(info, i);
                lua::push(state, method_info);

                auto value_name = g_function_info_get_symbol(method_info);
                if (value_name == nullptr) {
                    value_name = g_base_info_get_attribute(method_info, "c:identifier");
                    if (value_name == nullptr) {
                        value_name = g_base_info_get_name(method_info);
                    }
                }
                if (value_name != nullptr) {
                    std::cerr << "luacxx: Loaded " << namespace_name << " struct method named " << g_function_info_get_symbol(method_info) << std::endl;
                    lua_setglobal(state, value_name);
                }
            }

            break;
        }
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
                    std::cerr << "luacxx: Loaded " << namespace_name << " enum value named " << value_name << std::endl;
                    lua_setglobal(state, value_name);
                } else {
                    std::cerr << "luacxx: No useful name available for "
                        << namespace_name << " enum value named" << g_base_info_get_name(info) << std::endl;
                }
            }

            break;
        }
        case GI_INFO_TYPE_CONSTANT:
        {
            std::cerr << "luacxx: Loaded " << namespace_name << " constant value named " << g_base_info_get_name(info) << std::endl;
            std::cerr << lua::dump(state) << std::endl;

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

            lua_setglobal(state, value_name);
            break;
        }
        default:
        {
            lua_setglobal(state, g_base_info_get_name(info));
            std::cerr << "luacxx: No binding available for "
                << namespace_name << " " << type_name
                << " symbol named " << g_base_info_get_name(info) << std::endl;
        }
        }
    }

    return 0;
}

// A package.seachers loader that requires a GIRepository-visible namespace.
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

    // Found a namespace , so push a function to load it into the environment
    lua::push(state, gi_import, name);
    return 2;
}

// Returns a list of all loaded namespaces.
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

int luaopen_luacxx_search_GIRepository(lua_State* const state)
{
    lua::table::insert(lua::global(state, "package")["searchers"], gi_search);
    return 0;
}
