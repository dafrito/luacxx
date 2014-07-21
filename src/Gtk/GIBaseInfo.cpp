#include "GIBaseInfo.hpp"
#include "GObject.hpp"
#include "../convert/callable.hpp"
#include "../convert/string.hpp"
#include <sstream>

// Print this info's name and type
std::string lua::GIInfoType_tostring(GIInfoType info_type)
{
    switch (info_type) {
    case GI_INFO_TYPE_INVALID: return "invalid";
    case GI_INFO_TYPE_FUNCTION: return "function";
    case GI_INFO_TYPE_CALLBACK: return "callback";
    case GI_INFO_TYPE_STRUCT: return "struct";
    case GI_INFO_TYPE_BOXED: return "boxed";
    case GI_INFO_TYPE_ENUM: return "enum";
    case GI_INFO_TYPE_FLAGS: return "flags";
    case GI_INFO_TYPE_OBJECT: return "object";
    case GI_INFO_TYPE_INTERFACE: return "interface";
    case GI_INFO_TYPE_CONSTANT: return "constant";
    case GI_INFO_TYPE_UNION: return "union";
    case GI_INFO_TYPE_VALUE: return "value";
    case GI_INFO_TYPE_SIGNAL: return "signal";
    case GI_INFO_TYPE_VFUNC: return "vfunc";
    case GI_INFO_TYPE_PROPERTY: return "property";
    case GI_INFO_TYPE_FIELD: return "field";
    case GI_INFO_TYPE_ARG: return "arg";
    case GI_INFO_TYPE_TYPE: return "type";
    case GI_INFO_TYPE_INVALID_0:
    case GI_INFO_TYPE_UNRESOLVED: return "Unresolved";
    default:
        std::stringstream str;
        str << info_type;
        return str.str();
    }
}

std::string lua::GIBaseInfo_tostring(GIBaseInfo* info)
{
    std::stringstream str;

    auto info_type = g_base_info_get_type(info);
    switch (info_type) {
    case GI_INFO_TYPE_FUNCTION:
    case GI_INFO_TYPE_CALLBACK:
    case GI_INFO_TYPE_SIGNAL:
    case GI_INFO_TYPE_VFUNC:
    {
        auto return_type = g_callable_info_get_return_type(info);
        str << lua::GIBaseInfo_tostring(return_type) << " ";
        g_base_info_unref(return_type);

        str << g_base_info_get_name(info);

        str << "(";
        auto n_args = g_callable_info_get_n_args(info);
        for (int i = 0; i < n_args; ++i) {
            auto arg_info = g_callable_info_get_arg(info, i);
            str << lua::GIBaseInfo_tostring(arg_info);
            if (i < n_args - 1) {
                str << ", ";
            }
            g_base_info_unref(arg_info);
        }
        str << ")";
        return str.str();
    }
    case GI_INFO_TYPE_STRUCT:
    {
        str << "struct " << g_base_info_get_name(info) << " {";

        // Enumerate methods
        for (int i = 0; i < g_struct_info_get_n_methods(info); ++i) {
            auto method_info = g_struct_info_get_method(info, i);
            str << "\n\t" << lua::GIBaseInfo_tostring(method_info);
            g_base_info_unref(method_info);
        }

        // Enumerate fields
        for (int i = 0; i < g_struct_info_get_n_fields(info); ++i) {
            auto field_info = g_struct_info_get_field(info, i);
            str << "\n\t" << lua::GIBaseInfo_tostring(field_info);
            g_base_info_unref(field_info);
        }

        str << "\n};";
        return str.str();
    }
    case GI_INFO_TYPE_FIELD:
    {
        // Print the field of a struct or union.
        auto field_info = g_field_info_get_type(info);
        str << lua::GIBaseInfo_tostring(field_info) << " " << g_base_info_get_name(info) << ';';
        g_base_info_unref(field_info);
        return str.str();
    }
    case GI_INFO_TYPE_TYPE:
    {
        auto interface_type = g_type_info_get_interface(info);
        if (interface_type) {
            str << g_base_info_get_name(interface_type);
            g_base_info_unref(interface_type);
        } else {
            str << g_type_tag_to_string(g_type_info_get_tag(info));
        }
        return str.str();
    }
    case GI_INFO_TYPE_ARG:
    {
        // Print the argument's underlying type.
        auto arg_info = g_arg_info_get_type(info);
        auto name = lua::GIBaseInfo_tostring(arg_info);
        switch (g_arg_info_get_direction(info)) {
        case GI_DIRECTION_OUT:
            str << name << "*";
            return str.str();
        case GI_DIRECTION_INOUT:
            str << name << "&";
            return str.str();
        case GI_DIRECTION_IN:
            str << name;
            return str.str();
        }

        throw std::logic_error("Unreachable");
    }
    case GI_INFO_TYPE_OBJECT:
    {
        str << "object " << g_base_info_get_name(info) << " {";

        // Enumerate methods
        for (int i = 0; i < g_object_info_get_n_methods(info); ++i) {
            auto method_info = g_object_info_get_method(info, i);
            str << "\n\t" << lua::GIBaseInfo_tostring(method_info);
            g_base_info_unref(method_info);
        }

        // Enumerate fields
        for (int i = 0; i < g_object_info_get_n_fields(info); ++i) {
            auto field_info = g_object_info_get_field(info, i);
            str << "\n\t" << lua::GIBaseInfo_tostring(field_info);
            g_base_info_unref(field_info);
        }

        str << "\n};";
        return str.str();
    }
    case GI_INFO_TYPE_INTERFACE:
    {
        str << "interface " << g_base_info_get_name(info) << " {";

        // Enumerate methods
        for (int i = 0; i < g_interface_info_get_n_methods(info); ++i) {
            auto method_info = g_interface_info_get_method(info, i);
            str << "\n\t" << lua::GIBaseInfo_tostring(method_info);
            g_base_info_unref(method_info);
        }

        // Enumerate properties
        for (int i = 0; i < g_interface_info_get_n_properties(info); ++i) {
            auto property_info = g_interface_info_get_property(info, i);
            str << "\n\t" << lua::GIBaseInfo_tostring(property_info);
            g_base_info_unref(property_info);
        }

        // TODO Enumerate signals
        // TODO Enumerate vfuncs
        // TODO Enumerate constants

        str << "\n};";
        break;
    }
    case GI_INFO_TYPE_BOXED:
    case GI_INFO_TYPE_ENUM:
    case GI_INFO_TYPE_FLAGS:
    case GI_INFO_TYPE_CONSTANT:
    case GI_INFO_TYPE_UNION:
    case GI_INFO_TYPE_VALUE:
    case GI_INFO_TYPE_PROPERTY:
    case GI_INFO_TYPE_INVALID:
    case GI_INFO_TYPE_INVALID_0:
    case GI_INFO_TYPE_UNRESOLVED:
    default:
        str << lua::GIInfoType_tostring(info_type);
        break;
    }

    return str.str();
}

int GIBaseInfo_index(lua_State* const state)
{
    auto info = lua::get<GIBaseInfo*>(state, 1);
    auto name = lua::get<const char*>(state, 2);
    lua_settop(state, 0);

    auto info_type = g_base_info_get_type(info);
    switch (info_type) {
    case GI_INFO_TYPE_OBJECT:
    {
        lua::push(state, g_object_info_find_method(info, name));
        break;
    }
    case GI_INFO_TYPE_STRUCT:
    {
        lua::push(state, g_struct_info_find_method(info, name));
        break;
    }
    case GI_INFO_TYPE_INTERFACE:
    {
        lua::push(state, g_interface_info_find_method(info, name));
        break;
    }
    default:
        std::stringstream str;
        str << "Indexing is not supported for " << lua::GIBaseInfo_tostring(info);
        throw lua::error(str.str());
    }
    return 1;
}

int lua::GIBaseInfo_call(lua_State* const state)
{
    auto callable = lua::get<GICallableInfo*>(state, 1);

    // Allocate the necesssary space for our arguments
    std::vector<GIArgument> in_args;
    std::vector<GIArgument> out_args;

    // Skip the callable passed to __call.
    lua::index param(state, 2);

    if (g_callable_info_is_method(callable)) {
        GIArgument arg;
        arg.v_pointer = param.get<void*>();
        in_args.push_back(arg);
        ++param;
    }

    // Marshal Lua arguments into GObject parameters
    auto n_args = g_callable_info_get_n_args(callable);
    for (int i = 0; i < n_args; ++i) {
        auto arginfo = g_callable_info_get_arg(callable, i);

        GIArgument arg;

        // Get the argument type
        GITypeInfo argtype;
        g_arg_info_load_type(arginfo, &argtype);
        auto type_tag = g_type_info_get_tag(&argtype);

        if (g_arg_info_get_direction(arginfo) != GI_DIRECTION_OUT) {
            switch (type_tag) {
            case GI_TYPE_TAG_INTERFACE:
            case GI_TYPE_TAG_VOID:
                arg.v_pointer = param.get<void*>();
                break;
            case GI_TYPE_TAG_BOOLEAN:
                arg.v_boolean = param.get<bool>();
                break;
            case GI_TYPE_TAG_INT8:
                arg.v_int8 = param.get<char>();
                break;
            case GI_TYPE_TAG_UINT8:
                arg.v_uint8 = param.get<unsigned char>();
                break;
            case GI_TYPE_TAG_INT16:
                arg.v_int16 = param.get<short>();
                break;
            case GI_TYPE_TAG_UINT16:
                arg.v_uint16 = param.get<unsigned short>();
                break;
            case GI_TYPE_TAG_INT32:
                arg.v_int32 = param.get<int>();
                break;
            case GI_TYPE_TAG_UINT32:
                arg.v_uint32 = param.get<unsigned int>();
                break;
            case GI_TYPE_TAG_INT64:
                arg.v_int64 = param.get<long>();
                break;
            case GI_TYPE_TAG_UINT64:
                arg.v_uint64 = param.get<unsigned long>();
                break;
            case GI_TYPE_TAG_FLOAT:
                arg.v_float = param.get<float>();
                break;
            case GI_TYPE_TAG_DOUBLE:
                arg.v_double = param.get<double>();
                break;
            case GI_TYPE_TAG_FILENAME:
            case GI_TYPE_TAG_UTF8:
                arg.v_string = param.get<char*>();
                break;
            case GI_TYPE_TAG_GTYPE:
            case GI_TYPE_TAG_ARRAY:
            case GI_TYPE_TAG_GLIST:
            case GI_TYPE_TAG_GSLIST:
            case GI_TYPE_TAG_GHASH:
            case GI_TYPE_TAG_ERROR:
            case GI_TYPE_TAG_UNICHAR:
                throw lua::error(std::string("The type, ") + g_type_tag_to_string(type_tag) + ", is not yet supported.");
            }
            ++param;
        }

        switch (g_arg_info_get_direction(arginfo)) {
            case GI_DIRECTION_IN:
                in_args.push_back(arg);
                break;
            case GI_DIRECTION_OUT:
                out_args.push_back(arg);
                break;
            case GI_DIRECTION_INOUT:
                in_args.push_back(arg);
                out_args.push_back(arg);
        }

        g_base_info_unref(arginfo);
    }

    // Invoke the callable
    GIArgument return_value;
    GError *err = nullptr;
    g_function_info_invoke(
        callable,
        in_args.data(), in_args.size(),
        out_args.data(), out_args.size(),
        &return_value,
        &err
    );
    if (err) {
        throw lua::error(err->message);
    }

    // Marshal the return value, if necessary
    GITypeInfo return_type;
    g_callable_info_load_return_type(callable, &return_type);
    auto type_tag = g_type_info_get_tag(&return_type);

    switch (type_tag) {
    case GI_TYPE_TAG_BOOLEAN: lua::push(state, return_value.v_boolean); break;
    case GI_TYPE_TAG_INT8: lua::push(state, return_value.v_int8); break;
    case GI_TYPE_TAG_UINT8: lua::push(state, return_value.v_uint8); break;
    case GI_TYPE_TAG_INT16: lua::push(state, return_value.v_int16); break;
    case GI_TYPE_TAG_UINT16: lua::push(state, return_value.v_uint16); break;
    case GI_TYPE_TAG_INT32: lua::push(state, return_value.v_int32); break;
    case GI_TYPE_TAG_UINT32: lua::push(state, return_value.v_uint32); break;
    case GI_TYPE_TAG_INT64: lua::push(state, return_value.v_int64); break;
    case GI_TYPE_TAG_UINT64: lua::push(state, return_value.v_uint64); break;
    case GI_TYPE_TAG_FLOAT: lua::push(state, return_value.v_float); break;
    case GI_TYPE_TAG_DOUBLE: lua::push(state, return_value.v_double); break;
    case GI_TYPE_TAG_UTF8:
    case GI_TYPE_TAG_FILENAME:
        lua::push(state, return_value.v_string);
        break;
    case GI_TYPE_TAG_INTERFACE:
        lua::push(state, static_cast<GObject*>(return_value.v_pointer));
        break;
    case GI_TYPE_TAG_GTYPE:
    case GI_TYPE_TAG_ARRAY:
    case GI_TYPE_TAG_GLIST:
    case GI_TYPE_TAG_GSLIST:
    case GI_TYPE_TAG_GHASH:
    case GI_TYPE_TAG_ERROR:
    case GI_TYPE_TAG_UNICHAR:
    case GI_TYPE_TAG_VOID:
    default:
    {
        lua::push(state, return_value.v_pointer); break;
    }
    }

    return 1;
}

void lua::GIBaseInfo_metatable(const lua::index& mt)
{
    mt["__call"] = lua::GIBaseInfo_call;
    mt["__index"] = GIBaseInfo_index;
    mt["__tostring"] = lua::GIBaseInfo_tostring;

    mt["Destroy"] = lua_CFunction([](lua_State* const state) {
        g_base_info_unref(lua::get<GIBaseInfo*>(state, 1));
        return 0;
    });
}
