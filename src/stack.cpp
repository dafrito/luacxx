#include "stack.hpp"
#include "algorithm.hpp"
#include <iostream>
#include <sstream>

#include "convert/const_char_p.hpp"

lua::userdata_type::~userdata_type()
{
    // std::cerr << "Destroying type " << this << " named " << _name << std::endl;
}

bool lua::is_debugging(lua_State* const state)
{
    lua_getglobal(state, "debugging");
    bool debugging = lua_toboolean(state, -1);
    lua_pop(state, 1);
    return debugging;
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

char* lua::malloc(lua_State* const state, size_t size, const lua::userdata_storage& storage)
{
    if (is_debugging(state)) {
        if (size == 1) {
            std::cerr << "lua::malloc: Allocating " << size << " byte." << std::endl;
        } else {
            std::cerr << "lua::malloc: Allocating " << size << " bytes." << std::endl;
        }
    }

    // Get and push a chunk of memory from Lua to hold our metadata, as well as
    // the underlying value.
    char* block = static_cast<char*>(lua_newuserdata(state,
        size + sizeof(lua::userdata_block)
    ));

    // Create the metadata at the end of the memory block; lua_touserdata will return a
    // valid pointer.
    new (block + size) lua::userdata_block(storage);

    // Return a pointer to the data block
    return block;
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

int lua::__gc(lua_State* const state)
{
    if (!lua_getmetatable(state, 1)) {
        throw lua::error(state, "luacxx::__gc: No metatable available for __gc.");
    }
    lua::index mt(state, -1);

    try {
        lua::assert_type("luaxx::__gc", lua::type::table, mt);

        if (is_debugging(state)) {
            auto class_name = lua::class_name(state, 1);
            if (!class_name.empty()) {
                std::cerr << "luacxx: __gc: Destroying " << class_name << " of size " << lua::object_size(state, 1) << std::endl;
            } else {
                std::cerr << "luacxx: __gc: Destroying anonymous userdata of size " << lua::object_size(state, 1) << std::endl;
            }
        }

        auto destroy = lua::table::get(mt, "destroy");
        if (destroy.type().function()) {
            lua::call(destroy, lua::index(state, 1));
        }

        auto free_userdata = lua::table::get(mt, "free_userdata");
        if (free_userdata.type().function()) {
            lua::call(free_userdata, lua::index(state, 1));
        }
    } catch (lua::error& ex) {
        std::cerr << "Error occurred during Lua garbage collection: " << ex.what();
    }

    return 0;
}
