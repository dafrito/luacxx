#include "thread.hpp"
#include "algorithm.hpp"
#include "load.hpp"

#include "type/standard.hpp"
#include "type/numeric.hpp"

#include <iostream>

int main(int argc, char** argv)
{
    auto env = lua::create();

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

    // We were given a filename, so just read it and return
    auto callable = lua::load_file(env, argv[1]);
    for (int i = 0; i < argc; ++i) {
        lua::push(env, argv[i]);
    }
    lua::invoke(callable);

    return callable ? callable.get<int>() : 0;
}
