#include <iostream>

#include "counter_lua.hpp"

#include <luacxx/convert/const_char_p.hpp>
#include <luacxx/load.hpp>
#include <luacxx/thread.hpp>

int main()
{
    auto env = lua::create();
    open_counter(env);

    lua::run_string(env, R"(
        local counter = Counter.new(10)
        counter:add(5)
        assert(counter:get() == 15)
    )");

    std::cout << "Counter binding example passed." << std::endl;
    return 0;
}
