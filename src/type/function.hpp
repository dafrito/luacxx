#ifndef LUA_CXX_TYPE_FUNCTION_HEADER
#define LUA_CXX_TYPE_FUNCTION_HEADER

#include <functional>
#include <sstream>

#include "../algorithm.hpp"
#include "../stack.hpp"

/*

=head1 NAME

type/function.hpp - support for C functions

=head1 SYNOPSIS

    #include <luacxx/type/function.hpp>
    #include <luacxx/type/standard.hpp>
    #include <luacxx/type/numeric.hpp>

    // Add all arguments
    int add_several(lua::state* const state)
    {
        int sum = 0;
        for (int i = 1; i <= lua_gettop(state); ++i) {
            sum += lua::get<int>(state, i);
        }

        lua::push(state, sum);
        lua_replace(state, 1);
        return 1;
    }

    // Add two directly
    int add_two(const int a, const int b)
    {
        return a + b;
    }

    // Add two, but have the first come from the upvalues
    int adder(lua::state* const state)
    {
        auto first = lua::get<int>(state, lua_upvalueindex(state, 1));
        auto second = lua::get<int>(state, 1);

        lua_settop(state, 0);
        lua::push(state, first + second);
        return 1;
    }

    // Create a partial function that adds two values
    int make_adder(lua::state* const state)
    {
        auto first = lua::get<int>(state, 1);
        lua_settop(state, 0);

        lua::push_closure(state, adder, first);
        return 1;
    }

    // Open the "add" module
    int luaopen_add(lua::state* const state)
    {
        lua:thread env(state);

        env["Adder"] = make_adder;
        env["AddTwo"] = add_two;
        env["AddSeveral"] = add_several;

        env["AddDelta"] = lua::push_function<int(int)>(state, [](int first) {
            return first + 3;
        );

        return 0;
    }

    // And within Lua

    require "add";

    assert(4 == AddTwo(2, 2));
    assert(6 == AddSeveral(1, 2, 3));
    assert(5 == Adder(2)(3));
    assert(5 == AddDelta(2));

=head1 DESCRIPTION

    int my_func(lua::state* const state);

Lua-cxx provides support through lua::push and this header for the following
types:

=head4 lua::callable - std::function<lua::function>

=head4 lua_CFunction, lua::function

Lua provides direct support for a single C function type, called lua_CFunction
or lua::function. They appear in Lua identically to Lua-defined functions (
though perhaps with a telling memory address). Lua-cxx provides support for
other function types, but these must ultimately end with a lua::function if they
are to do any work.

The state is populated with the arguments passed to it. The function can then
work on the stack. Once complete, the function should return the number of
arguments that will be returned. The arguments are taken from the top, so the
initial arguments do not need to be removed.

    int demo(lua::state* const state)
    {
        // Pull arguments
        auto id = lua::get<int>(state, 1);
        auto value = lua::get<bool>(state, 2);

        auto result = set_some_inner_value(id, value);

        // Return the result
        lua_settop(state, 0);
        lua::push(state, result);
        return 1;
    }

=head4 lua_pushcfunction(state, lua::function)

Pushes the given callable C function onto the stack.

    int demo(lua::state* const state)
    {
        // ... same as above ...
    }

    lua::push(state, demo);

*/

namespace lua {

typedef lua_CFunction function;
typedef std::function<int(lua::state* const)> callable;

}

namespace lua {

template <>
struct Push<lua::function>
{
    static void push(lua::state* const state, lua::function callable)
    {
        lua_pushcclosure(state, callable, 0);
    }
};

template <>
struct Store<lua::function>
{
    static void store(lua::function& destination, const lua::index& source)
    {
        destination = lua_tocfunction(source.state(), source.pos());
    }
};

static int invoke_callable(lua::state* const state)
{
    auto callable = lua::get<lua::callable*>(lua::index(state, lua_upvalueindex(1)));
    try {
        return (*callable)(state);
    } catch (lua::error& ex) {
        lua::push(state, ex);
        lua_error(state);
        throw std::logic_error("lua_error must never return");
    }
}

template <>
struct Push<lua::callable>
{
    static void push(lua::state* const state, const lua::callable& callable)
    {
        Construct<lua::callable>::construct(state, callable);
        lua_pushcclosure(state, invoke_callable, 1);
    }
};

template <>
struct Store<lua::callable>
{
    static void store(lua::callable& destination, const lua::index& source)
    {
        lua_getupvalue(source.state(), source.pos(), 1);
        lua::store_userdata<lua::userdata_storage::value>(destination, lua::index(source.state(), -1));
        lua_pop(source.state(), 1);
    }
};

} // namespace lua

namespace {

struct ArgStop {};

template <typename Callee, typename RV, typename Arg, typename... Parameters>
struct Invoke
{
    template <typename... Arguments>
    static void invoke(const Callee& func, lua::index& index, Arguments... arguments)
    {
        Invoke<Callee, RV, Parameters...>::template invoke<Arguments..., Arg>(
            func, index, arguments..., lua::get<Arg>(index++)
        );
    }
};

template <typename Callee, typename RV>
struct Invoke<Callee, RV, ArgStop>
{
    template <typename... Arguments>
    static void invoke(const Callee& func, lua::index& index, Arguments... arguments)
    {
        lua::clear(index.state());
        lua::push(index.state(), func(arguments...));
    }
};

template <typename Callee>
struct Invoke<Callee, void, ArgStop>
{
    template <typename... Arguments>
    static void invoke(const Callee& func, lua::index& index, Arguments... arguments)
    {
        lua::clear(index.state());
        func(arguments...);
    }
};

} // namespace anonymous

/*

=head4 struct lua::Push<RV(*)(Args...)>

This allows function pointers to be pushed directly onto the stack. The
function pointer must be comprised of objects that can be pushed, or void.

    int multiply_direct(int a, int b)
    {
        return a * b;
    }

    lua::push(state, multiply_direct);

This also supports C++ method pointers:

    struct Foo {
        void multiply(int a, int b);
    };

    // Equivalent to void get(Foo*, int, int);
    lua::push(state, &Foo::get);

=head4 struct lua::Push<std::function<RV(Args...)>>

This allows std::functions to be pushed directly onto the stack. This follows
the same rules as the function-pointer version, but works for anything that
std::function supports. Notably, this allows lambdas to be pushed:

    env["Multiply"] = std::function<int(int, int)>([](int a, int b) {
        return a * b;
    });

Tragically, you can't omit the std::function. Lambdas don't have an accessible
signature, so it needs to be specified externally using std::function.

*/

namespace lua {

template <typename RV, typename... Args>
int invoke_callable(lua::state* const state)
{
    auto wrapped = lua::get<std::function<RV(Args...)>>(
        state, lua_upvalueindex(1)
    );

    if (lua::size(state) < sizeof...(Args)) {
        std::stringstream msg;
        msg << "Function expects at least "
            << sizeof...(Args)
            << " argument" << (sizeof...(Args) == 1 ? "" : "s");
        if (lua::size(state) > 1) {
            msg << " but only " << lua::size(state) << " were given";
        } else if (lua::size(state) > 0) {
            msg << " but only " << lua::size(state) << " was given";
        } else {
            msg << " but none were given";
        }
        throw lua::error(msg.str());
    }

    lua::index index(state, 1);
    Invoke<decltype(wrapped), RV, Args..., ArgStop>::template invoke<>(wrapped, index);
    return 1;
}

template <typename RV, typename... Args>
struct Push<RV(*)(Args...)>
{
    static void push(lua::state* const state, RV(*func)(Args...))
    {
        lua::push(state, std::function<RV(Args...)>(func));
    }
};

template <typename RV, typename... Args>
struct Push<std::function<RV(Args...)>>
{
    static void push(lua::state* const state, const std::function<RV(Args...)>& callable)
    {
        Construct<std::function<RV(Args...)>>::construct(state, callable);
        lua_pushcclosure(state, invoke_callable<RV, Args...>, 1);
    }
};

template <typename RV>
struct Push<RV(*)(lua::state* const)>
{
    static void push(lua::state* const state, RV(*func)(lua::state* const))
    {
        lua::push(state, lua::callable([=](lua::state* const state) {
            lua::push(state, func(state));
            lua_replace(state, 1);
            lua_settop(state, 1);
            return 1;
        }));
    }
};

template <typename RV>
struct Push<std::function<RV(lua::state* const)>>
{
    static void push(lua::state* const state, const std::function<RV(lua::state* const)>& func)
    {
        lua::push(state, lua::callable([=](lua::state* const state) {
            lua::push(state, func(state));
            lua_replace(state, 1);
            lua_settop(state, 1);
            return 1;
        }));
    }
};

/*

=head4 lua::push_function<Signature>(state, callable)

Pushes the callable with the given function signature onto the Lua stack. This
is useful if you want to be a bit clearer in how your functions are being
converted into callables.

*/

template <typename Signature>
static lua::index push_function(lua::state* const state, std::function<Signature> callable)
{
    return lua::push(state, callable);
}

/*

=head4 lua::push_closure(state, callable, upvalues...);

Pushes the given callable onto the stack. The upvalues provided will be saved
with the function, and made available using the lua_upvalueindex(n) accessor.

The following example shows pushing a C function onto the stack, and then shows
the function accessing its upvalues:

    int get_worker(lua::state* const state)
    {
        auto url = lua::get<std::string>(state, 1);
        lua_settop(state, 0);

        // Return the worker function
        lua::push_closure(work, url);
        return 1;
    }

    void work()
    {
        // Get the URL, saved from when this worker was made
        auto url = lua::get<std::string>(state, lua_upvalueindex(1));

        // Upvalues don't interfere with regular arguments
        auto units_to_perform = lua::get<int>(state, 1);

        connect_to_the_server(url);
        while (units_to_perform-- > 0) {
            ... work ...
        }
    }

    // Meanwhile, in Lua...

    local workers = {};
    for i=1, 100 do
        -- Connect to each server in the network
        local worker = get_worker("example.com/server/" .. i);
        table.insert(workers, worker);
    end;

    -- Start some work
    for _, worker in ipairs(workers) do
        worker(1000);
    end;

=head4 lua_pushcclosure(state, lua::function, int upvalues)

=head4 int lua_upvalueindex(int offset)

Returns the stack index that corresponds to the upvalue at the specified
offset. Upvalues are used to associate arbitrary Lua data with C functions,
but are rare to actually need in practice.

*/

template <typename... Upvalues>
static lua::index push_closure(lua::state* const state, lua::function callable, Upvalues... upvalues)
{
    lua::push(state, upvalues...);
    lua_pushcclosure(state, callable, sizeof...(Upvalues));
    return lua::index(state, -1);
}

} // namespace lua

#endif // LUA_CXX_TYPE_FUNCTION_HEADER
