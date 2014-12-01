#include "stack.hpp"
#include "algorithm.hpp"
#include <sstream>

#include "convert/const_char_p.hpp"
#include "convert/string.hpp"
#include "convert/callable.hpp"

lua::userdata_type::~userdata_type()
{
}

static bool debugging_allowed = false;

void lua::allow_debugging(bool allowed)
{
    debugging_allowed = allowed;
}

bool lua::is_debugging_allowed()
{
    #ifdef LUACXX_FASTEST
    return false;
    #else
    return debugging_allowed;
    #endif
}

bool lua::is_debugging(lua_State* const state)
{
    #ifdef LUACXX_FASTEST
    // Making this a compile-time constant improves performance by 10%
    return false;
    #else
    if (!lua::is_debugging_allowed()) {
        return false;
    }
    lua_getglobal(state, "debugging");
    bool debugging = lua_toboolean(state, -1);
    lua_pop(state, 1);
    return debugging;
    #endif
}

std::string lua::traceback(lua_State* const state, const int toplevel)
{
    #if LUA_VERSION_NUM >= 502
        std::string rv;
        luaL_traceback(state, state, NULL, toplevel);
        rv = lua::get<std::string>(state, -1);
        lua_pop(state, 1);
        return rv;
    #else
        auto getter = lua::global(state, "debug")["traceback"];
        return getter("", topLevel).get<std::string>().substr(1);
    #endif
}

std::string lua::dump(lua_State* const state)
{
    std::stringstream str;

    str << "Lua stack (" << lua::size(state) << " ";
    if (lua::size(state) == 1) {
        str << "item";
    } else {
        str << "items";
    }

    str << "): ";

    for (lua::index iter(state, 1); iter; ++iter) {
        switch (iter.type().get()) {
        case lua::type::boolean:
            str << (lua_toboolean(state, iter.pos()) ? "true" : "false");
            break;
        case lua::type::string:
        {
            std::string value(lua_tostring(state, iter.pos()));
            if (value.size() > 30) {
                str << '"' << value.substr(0, 30) << "\"...";
            } else {
                str << '"' << value << '"';
            }
            break;
        }
        case lua::type::number:
        {
            // Push a copy so we don't corrupt the original numeric value by
            // converting it to a string.
            lua_pushvalue(state, iter.pos());
            str << lua_tostring(state, -1);
            lua_pop(state, 1);
            break;
        }
        case lua::type::userdata:
        {
            auto name = lua::class_name(iter);
            if (!name.empty()) {
                str << name << "(size=" << lua_rawlen(iter.state(), iter.pos()) << ')';
            } else {
                str << iter.type().name() << "(size=" << lua_rawlen(iter.state(), iter.pos()) << ')';
            }
            str << "@" << lua_topointer(iter.state(), iter.pos());
            break;
        }
        case lua::type::table:
            str << iter.type().name() << "(size=" << lua_rawlen(iter.state(), iter.pos()) << ')';
            break;
        case lua::type::function:
        case lua::type::thread:
        {
            str << iter.type().name() << "@";
            str << lua_topointer(iter.state(), iter.pos());
            break;
        }
        default:
            str << iter.type().name();
        }
        if (iter.pos() != lua::top(state).pos()) {
            str << ", ";
        }
    }

    return str.str();
}

template <>
void lua::get<void>(const lua::index& source)
{
}

size_t lua::object_size(lua_State* const state, const int pos)
{
    return lua_rawlen(state, pos) - sizeof(lua::userdata_block);
}

lua::userdata_block* lua::get_userdata_block(lua_State* const state, const int pos)
{
    char* block = static_cast<char*>(lua_touserdata(state, pos));
    if (block == nullptr) {
        return nullptr;
    }
    return reinterpret_cast<lua::userdata_block*>(
        block + lua::object_size(state, pos)
    );
}

// Allow noop invocations from variadic templates
lua::index lua::push(lua_State* const state)
{
    return lua::index(state, -1);
}

lua::userdata_block* lua::malloc(lua_State* const state, size_t size)
{
    if (lua::is_debugging(state)) {
        std::stringstream str;
        str << "Allocating ";
        if (size == 1) {
            str << size << " byte.";
        } else {
            str << size << " bytes.";
        }
        lua::logEntercm(state, "Lua memory allocations", str.str());
    }

    lua::userdata_block* userdata_block;
    if (size > 0) {
        // Get and push a chunk of memory from Lua to hold our metadata, as well as
        // the underlying value.
        char* raw_userdata = static_cast<char*>(lua_newuserdata(state,
            size + sizeof(lua::userdata_block)
        ));

        // Create the metadata at the end of the memory block; lua_touserdata will return a
        // valid pointer.
        userdata_block = new (raw_userdata + size) lua::userdata_block(raw_userdata);
    } else {
        char* raw_userdata = static_cast<char*>(lua_newuserdata(state,
            sizeof(lua::userdata_block)
        ));

        userdata_block = new (raw_userdata) lua::userdata_block;
    }

    // Return a pointer to the data block
    if (lua::is_debugging(state)) {
        lua::logLeave(state);
    }
    return userdata_block;
}

int lua::__tostring(lua_State* const state)
{
    std::string class_name(lua::class_name(state, 1));

    std::stringstream str;
    if (!class_name.empty()) {
        str << class_name << "@";
    } else {
        str << "userdata[size=" << lua_rawlen(state, 1) << "]@";
    }

    str << lua_topointer(state, 1);

    lua_pushstring(state, str.str().c_str());
    return 1;
}

void lua::lua_error_metatable(lua_State* const state, const int pos)
{
    lua::index mt(state, pos);

    mt["what"] = &lua::error::what;
    mt["__tostring"] = &lua::error::what;
}
