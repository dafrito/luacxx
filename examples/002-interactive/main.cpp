#include <iostream>

#include "luacxx/stack.hpp"
#include "luacxx/convert/const_char_p.hpp"
#include "luacxx/convert/string.hpp"
#include "luacxx/convert/char_p.hpp"
#include "luacxx/convert/numeric.hpp"
#include "luacxx/thread.hpp"
#include "luacxx/algorithm.hpp"
#include "luacxx/load.hpp"

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

    auto default_cpath = env["package"]["cpath"].get<std::string>();
    while (default_cpath.find(";;") != std::string::npos) {
        default_cpath.replace(
            default_cpath.find(";;"),
            2,
            ";"
        );
    }

    if (std::getenv("LUA_CPATH") != nullptr) {
        std::string LUA_CPATH(std::getenv("LUA_CPATH"));
        while (LUA_CPATH.find(";;") != std::string::npos) {
            LUA_CPATH.replace(
                LUA_CPATH.find(";;"),
                2,
                default_cpath
            );
        }
        env["package"]["cpath"] = LUA_CPATH;
    }

    auto default_path = env["package"]["path"].get<std::string>();
    while (default_path.find(";;") != std::string::npos) {
        default_path.replace(
            default_path.find(";;"),
            2,
            ";"
        );
    }

    if (std::getenv("LUA_PATH") != nullptr) {
        std::string LUA_PATH(std::getenv("LUA_PATH"));
        if (!LUA_PATH.empty()) {
            while (LUA_PATH.find(";;") != std::string::npos) {
                LUA_PATH.replace(
                    LUA_PATH.find(";;"),
                    2,
                    default_path
                );
            }
            env["package"]["path"] = LUA_PATH;
        }
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
