#include <fstream>
#include <sstream>

#include "luacxx/load.hpp"
#include "luacxx/error.hpp"

namespace {
    constexpr std::size_t chunk_size = 4096;
    constexpr char empty_line = '\n';

    struct LuaReadingData
    {
        std::istream& stream;
        char buffer[chunk_size];
        bool atStart;
        LuaReadingData(std::istream& stream) :
            stream(stream),
            atStart(true)
        {
        }
    };

    const char* readStdStream(lua_State* const, void* data, size_t* size)
    {
        LuaReadingData* d = static_cast<LuaReadingData*>(data);
        if (d->atStart) {
            d->atStart = false;
            d->stream.read(d->buffer, 2);
            const auto prefix_size = d->stream.gcount();
            if (d->stream.bad()) {
                throw lua::error("I/O error while reading the start of a Lua stream.");
            }

            if (prefix_size == 2 && d->buffer[0] == '#' && d->buffer[1] == '!') {
                // Shebang, so ignore the rest of the line
                std::string shebangLine;
                std::getline(d->stream, shebangLine);
                if (d->stream.bad()) {
                    throw lua::error("I/O error while skipping a Lua shebang line.");
                }

                // Return a newline so line counts are correct
                *size = 1;
                return &empty_line;
            } else {
                // Nothing found, so head back to the start of the file
                d->stream.clear();
                d->stream.seekg(0);
                if (!d->stream) {
                    throw lua::error("Failed to seek to the start of a Lua stream.");
                }
            }
        }

        d->stream.read(d->buffer, chunk_size);
        *size = static_cast<size_t>(d->stream.gcount());

        if (d->stream.bad()) {
            throw lua::error("I/O error while reading a Lua stream.");
        }

        if (d->stream.fail() && !d->stream.eof()) {
            throw lua::error("Failed while reading a Lua stream.");
        }

        if (*size == 0) {
            return NULL;
        }

        return d->buffer;
    }

    lua::index do_post_load(lua_State* const state, const int rv)
    {
        switch (rv) {
            case LUA_ERRSYNTAX:
                throw lua::error(std::string("Syntax error during compilation:\n") + lua_tostring(state, -1));
            case LUA_ERRMEM:
                throw lua::error(std::string("Memory allocation error during compilation:\n") + lua_tostring(state, -1));
        }
        return lua::index(state, -1);
    }

} // namespace anonymous

lua::index lua::load_file(lua_State* const state, const std::string& file)
{
    std::ifstream stream(file, std::ios::in);
    if (!stream) {
        throw lua::error(state, std::string("File stream could not be opened for '") + file + "'");
    }

    return lua::load_file(state, stream, file);
}

lua::index lua::load_file(lua_State* const state, std::istream& stream, const std::string& name)
{
    LuaReadingData d(stream);
    if (!stream) {
        throw lua::error(state, std::string("Input stream is invalid for '") + name + "'");
    }

    return do_post_load(state, lua_load(state, &readStdStream, &d, name.c_str()
        #if LUA_VERSION_NUM >= 502
            // Account for the extra mode parameter introduced in 5.2
            , NULL
        #endif
    ));
}

lua::index lua::load_file(lua_State* const state, const char* filename)
{
    return lua::load_file(state, std::string(filename));
}

lua::index lua::load_string(lua_State* const state, const std::string& input)
{
    return lua::load_string(state, input.c_str());
}

lua::index lua::load_string(lua_State* const state, const char* input)
{
    do_post_load(state, luaL_loadstring(state, input));
    return lua::index(state, -1);
}
