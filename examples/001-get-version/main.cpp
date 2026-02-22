#include <luacxx/thread.hpp>
#include <luacxx/stack.hpp>
#include <luacxx/convert/const_char_p.hpp>
#include <luacxx/convert/string.hpp>
#include <luacxx/convert/char_p.hpp>
#include <luacxx/convert/numeric.hpp>
#include <luacxx/algorithm.hpp>
#include <luacxx/load.hpp>

int main() {
    // Create a new Lua environment to play with.
    auto env = lua::create();

    // Introduce a global into Lua
    env["foo"] = "No time";

    // Run some Lua code directly
    lua::run_string(env, "assert(foo == 'No time')");

    // Retrieve a global
    auto value = env["foo"].get<std::string>();
    assert(value == "No time");

    lua::run_string(env, "print(_VERSION)");

    return 0;
}
