#include "lua-cxx/thread.hpp"
#include "lua-cxx/algorithm.hpp"
#include "lua-cxx/load.hpp"
#include "lua-cxx/type/standard.hpp"
#include "lua-cxx/type/numeric.hpp"

#include <iostream>

int run_interactive(lua::thread& env)
{
    std::string line;
    while (std::cin) {
        std::getline(std::cin, line);
        try {
            if (line.size() > 0) {
                lua::run_string(env, line);
            }
        } catch (lua::error& err) {
            std::cerr << std::endl << err.what() << std::endl;
        }
    }

    return 0;
}

int on_panic(lua_State* const state)
{
    throw lua::error(lua::get<const char*>(state, -1));
}

int main(int argc, char** argv)
{
    auto env = lua::create();

    lua_atpanic(env, on_panic);

    auto LUA_CPATH = std::getenv("LUA_CPATH");
    if (LUA_CPATH) {
        env["package"]["cpath"] = LUA_CPATH;
    }

    auto LUA_PATH = std::getenv("LUA_PATH");
    if (LUA_PATH) {
        env["package"]["path"] = LUA_PATH;
    }

    if (argc == 1) {
        // Behave interactively if no filename was given.
        return run_interactive(env);
    }

    try {
        // We were given a filename, so just read it and return
        auto callable = lua::load_file(env, argv[1]);
        for (int i = 0; i < argc; ++i) {
            lua::push(env, argv[i]);
        }
        lua::invoke(callable);

        return callable ? callable.get<int>() : 0;
    } catch (lua::error& ex) {
        std::cerr << ex.what() << std::endl;
        return -1;
    }
}
