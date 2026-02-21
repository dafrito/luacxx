#ifndef luacxx_convert_callable_INCLUDED
#define luacxx_convert_callable_INCLUDED

#include <functional>
#include <sstream>

#include "../algorithm.hpp"
#include "../stack.hpp"
#include "../reference.hpp"

/*

=head1 NAME

convert/callable.hpp - support for C functions

=head1 SYNOPSIS

    #include <luacxx/convert/callable.hpp>
    #include <luacxx/convert/string.hpp>
    #include <luacxx/convert/numeric.hpp>

    // Add all arguments
    int add_several(lua_State* const state)
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
    int adder(lua_State* const state)
    {
        auto first = lua::get<int>(state, lua_upvalueindex(state, 1));
        auto second = lua::get<int>(state, 1);

        lua_settop(state, 0);
        lua::push(state, first + second);
        return 1;
    }

    // Create a partial function that adds two values
    int make_adder(lua_State* const state)
    {
        auto first = lua::get<int>(state, 1);
        lua_settop(state, 0);

        lua::push_closure(state, adder, first);
        return 1;
    }

    // Open the "add" module
    int luaopen_add(lua_State* const state)
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

    int my_func(lua_State* const state);

Lua-cxx provides support through lua::push and this header for the following
types:

=head4 lua::callable - std::function<int(lua_State*)>

=head4 lua_CFunction, lua_CFunction

Lua provides direct support for a single C function type, called lua_CFunction
or lua_CFunction. They appear in Lua identically to Lua-defined functions (
though perhaps with a telling memory address). Lua-cxx provides support for
other function types, but these must ultimately end with a lua_CFunction if they
are to do any work.

The state is populated with the arguments passed to it. The function can then
work on the stack. Once complete, the function should return the number of
arguments that will be returned. The arguments are taken from the top, so the
initial arguments do not need to be removed.

    int demo(lua_State* const state)
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

=head4 lua_pushcfunction(state, lua_CFunction)

Pushes the given callable C function onto the stack.

    int demo(lua_State* const state)
    {
        // ... same as above ...
    }

    lua::push(state, demo);

*/

namespace lua {

typedef std::function<int(lua_State* const)> callable;

}

namespace lua {

template <>
struct Push<lua_CFunction>
{
    static void push(lua_State* const state, lua_CFunction callable)
    {
        lua_pushcclosure(state, callable, 0);
    }
};

template <>
struct Store<lua_CFunction>
{
    static void store(lua_CFunction& destination, lua_State* const state, const int source)
    {
        destination = lua_tocfunction(state, source);
    }
};

int invoke_callable(lua_State* const state);

template <>
struct Push<lua::callable>
{
    static void push(lua_State* const state, const lua::callable& callable)
    {
        Construct<lua::callable>::construct(state, callable);
        lua_pushcclosure(state, invoke_callable, 1);
    }
};

template <>
struct Store<lua::callable>
{
    static void store(lua::callable& destination, lua_State* const state, const int source)
    {
        if (lua_type(state, source) == LUA_TNIL) {
            destination = nullptr;
            return;
        }
        lua_getupvalue(state, source, 1);
        auto block = lua::get_userdata_block(state, -1);
        destination = *block->cast<lua::callable>(state);
        lua_pop(state, 1);
    }
};

} // namespace lua

LUA_METATABLE_NAMED(lua::callable);

namespace {

struct ArgStop {};

template <typename Callee, typename RV, typename Arg, typename... Parameters>
struct Invoke
{
    template <typename... Arguments>
    static int invoke(const Callee& func, lua::index& index, Arguments... arguments)
    {
        return Invoke<Callee, RV, Parameters...>::template invoke<Arguments..., Arg>(
            func, index, arguments..., lua::get<Arg>(index++)
        );
    }
};

template <typename Callee, typename RV>
struct Invoke<Callee, RV, ArgStop>
{
    template <typename... Arguments>
    static int invoke(const Callee& func, lua::index& index, Arguments... arguments)
    {
        lua::push(index.state(), func(arguments...));
        return 1;
    }
};

template <typename Callee>
struct Invoke<Callee, void, ArgStop>
{
    template <typename... Arguments>
    static int invoke(const Callee& func, lua::index&, Arguments... arguments)
    {
        func(arguments...);
        return 0;
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
int invoke_callable(lua_State* const state)
{
    auto wrapped = lua::get_userdata_block(state, lua_upvalueindex(1))->cast<std::function<RV(Args...)>>(state);

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
        throw lua::error(state, msg.str());
    }

    lua::index index(state, 1);
    return Invoke<decltype(*wrapped), RV, Args..., ArgStop>::template invoke<>(*wrapped, index);
}

template <typename RV, typename... Args>
struct Push<RV(*)(Args...)>
{
    static void push(lua_State* const state, RV(*func)(Args...))
    {
        lua::push(state, std::function<RV(Args...)>(func));
    }
};

template <typename RV>
struct Push<RV(*)(lua_State* const)>
{
    static void push(lua_State* const state, RV(*func)(lua_State* const))
    {
        lua::push(state, lua::callable([=](lua_State* const state) {
            lua::push(state, func(state));
            lua_replace(state, 1);
            lua_settop(state, 1);
            return 1;
        }));
    }
};

template <>
struct Push<void(*)(lua_State* const)>
{
    static void push(lua_State* const state, void(*func)(lua_State* const))
    {
        lua::push(state, lua::callable([=](lua_State* const state) {
            func(state);
            return 0;
        }));
    }
};

template <>
struct Push<std::function<void(lua_State* const)>>
{
    static void push(lua_State* const state, const std::function<void(lua_State* const)>& func)
    {
        lua::push(state, lua::callable([=](lua_State* const state) {
            func(state);
            return 0;
        }));
    }
};

template <typename RV>
struct Push<std::function<RV(lua_State* const)>>
{
    static void push(lua_State* const state, const std::function<RV(lua_State* const)>& func)
    {
        lua::push(state, lua::callable([=](lua_State* const state) {
            lua::push(state, func(state));
            lua_replace(state, 1);
            lua_settop(state, 1);
            return 1;
        }));
    }
};

template <typename Object, typename... Args>
struct Push<void(Object::*)(Args...)>
{
    static void push(lua_State* const state, void(Object::* func)(Args...))
    {
        lua::push(state, std::function<void(Object*, Args...)>(
            std::mem_fn(func)
        ));
    }
};

template <typename RV, typename Object, typename... Args>
struct Push<RV(Object::*)(Args...)>
{
    static void push(lua_State* const state, RV(Object::* func)(Args...))
    {
        lua::push(state, std::function<RV(Object*, Args...)>(
            std::mem_fn(func)
        ));
    }
};

template <typename Object, typename... Args>
struct Push<void(Object::*)(Args...) const>
{
    static void push(lua_State* const state, void(Object::* func)(Args...) const)
    {
        lua::push(state, std::function<void(Object*, Args...)>(
            std::mem_fn(func)
        ));
    }
};

template <typename RV, typename Object, typename... Args>
struct Push<RV(Object::*)(Args...) const>
{
    static void push(lua_State* const state, RV(Object::* func)(Args...) const)
    {
        lua::push(state, std::function<RV(Object*, Args...)>(
            std::mem_fn(func)
        ));
    }
};


template <typename Object>
struct Push<void(Object::*)(lua_State* const state)>
{
    static void push(lua_State* const state, void(Object::* func)(lua_State* const))
    {
        auto inner = std::function<void(Object*, lua_State* const)>(
            std::mem_fn(func)
        );
        lua::push(state, lua::callable([=](lua_State* const state) {
            inner(
                lua::get<Object*>(state, 1),
                state
            );
            return 0;
        }));
    }
};

template <typename RV, typename Object>
struct Push<RV(Object::*)(lua_State* const state)>
{
    static void push(lua_State* const state, RV(Object::* func)(lua_State* const))
    {
        auto inner = std::function<RV(Object*, lua_State* const)>(
            std::mem_fn(func)
        );
        lua::push(state, lua::callable([=](lua_State* const state) {
            lua::push(state, inner(
                lua::get<Object*>(state, 1),
                state
            ));
            return 1;
        }));
    }
};

template <typename Object>
struct Push<void(Object::*)(lua_State* const state) const>
{
    static void push(lua_State* const state, void(Object::* func)(lua_State* const) const)
    {
        auto inner = std::function<void(Object*, lua_State* const)>(
            std::mem_fn(func)
        );
        lua::push(state, lua::callable([=](lua_State* const state) {
            inner(
                lua::get<Object*>(state, 1),
                state
            );
            return 1;
        }));
    }
};

template <typename RV, typename Object>
struct Push<RV(Object::*)(lua_State* const state) const>
{
    static void push(lua_State* const state, RV(Object::* func)(lua_State* const) const)
    {
        auto inner = std::function<RV(Object*, lua_State* const)>(
            std::mem_fn(func)
        );
        lua::push(state, lua::callable([=](lua_State* const state) {
            lua::push(state, inner(
                lua::get<Object*>(state, 1),
                state
            ));
            return 1;
        }));
    }
};

template <typename Object>
struct Push<int(Object::*)(lua_State* const state)>
{
    static void push(lua_State* const state, int(Object::* func)(lua_State* const))
    {
        auto inner = std::function<int(Object*, lua_State* const)>(
            std::mem_fn(func)
        );
        lua::push(state, lua::callable([=](lua_State* const state) {
            return inner(
                lua::get<Object*>(state, 1),
                state
            );
        }));
    }
};

template <typename Object>
struct Push<int(Object::*)(lua_State* const state) const>
{
    static void push(lua_State* const state, int(Object::* func)(lua_State* const) const)
    {
        auto inner = std::function<int(Object*, lua_State* const)>(
            std::mem_fn(func)
        );
        lua::push(state, lua::callable([=](lua_State* const state) {
            return inner(
                lua::get<Object*>(state, 1),
                state
            );
        }));
    }
};

template <typename RV, typename... Args>
struct Push<std::function<RV(Args...)>>
{
    static void push(lua_State* const state, const std::function<RV(Args...)>& callable)
    {
        Construct<std::function<RV(Args...)>>::construct(state, callable);
        lua_pushcclosure(state, invoke_callable<RV, Args...>, 1);
    }
};

template <typename... Args>
struct Push<std::function<void(Args...)>>
{
    static void push(lua_State* const state, const std::function<void(Args...)>& callable)
    {
        Construct<std::function<void(Args...)>>::construct(state, callable);
        lua_pushcclosure(state, invoke_callable<void, Args...>, 1);
    }
};

template <typename RV, typename... Args>
struct Get<std::function<RV(Args...)>>
{
static std::function<RV(Args...)> get(lua_State* const state, const int pos)
{
    lua::reference callable(state, pos);
    return std::function<RV(Args...)>([callable](Args... args) -> decltype(lua::call<RV>(callable, args...)) {
        return lua::call<RV>(callable, args...);
    });
}
};

template <typename Arg, typename... Rest>
struct AppendTypenames
{
    static void appendTypenames(std::stringstream& str)
    {
        str << lua::Metatable<Arg>::info().name() << ", ";
        AppendTypenames<Rest...>::appendTypenames(str);
    }
};

template <typename Arg>
struct AppendTypenames<Arg, ArgStop>
{
    static void appendTypenames(std::stringstream& str)
    {
        str << lua::Metatable<Arg>::info().name();
    }
};

template <>
struct AppendTypenames<ArgStop>
{
    static void appendTypenames(std::stringstream&)
    {
    }
};

template <typename RV, typename... Args>
struct Metatable<std::function<RV(Args...)>>
{
    static const lua::userdata_type& info()
    {
        static lua::userdata_type _info;
        if (!_info.has_name()) {
            std::stringstream str;
            str << "std::function<";
            str << lua::Metatable<RV>::info().name();
            str << "(";
            AppendTypenames<Args..., ArgStop>::appendTypenames(str);
            str << ")>";
            _info.set_name(str.str());

            _info.add_cast<std::function<RV(Args...)>>();
        }
        return _info;
    }

    static bool metatable(lua_State* const, const int, void* const)
    {
        return true;
    }
};

template <typename RV, typename... Args>
struct Metatable<RV(Args...)>
{
    static const lua::userdata_type& info()
    {
        static lua::userdata_type _info;
        if (!_info.has_name()) {
            std::stringstream str;
            str << lua::Metatable<RV>::info().name();
            str << "(";
            AppendTypenames<Args..., ArgStop>::appendTypenames(str);
            str << ")";
            _info.set_name(str.str());

            _info.add_cast<RV(Args...)>();
        }
        return _info;
    }

    static bool metatable(lua_State* const, const int, void* const)
    {
        return true;
    }
};

/*

=head4 lua::push_function<Signature>(state, callable)

Pushes the callable with the given function signature onto the Lua stack. This
is useful if you want to be a bit clearer in how your functions are being
converted into callables.

*/

template <typename Signature>
static lua::index push_function(lua_State* const state, std::function<Signature> callable)
{
    return lua::push(state, callable);
}

/*

=head4 lua::push_closure(state, callable, upvalues...);

Pushes the given callable onto the stack. The upvalues provided will be saved
with the function, and made available using the lua_upvalueindex(n) accessor.

The following example shows pushing a C function onto the stack, and then shows
the function accessing its upvalues:

    int get_worker(lua_State* const state)
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
static lua::index push_closure(lua_State* const state, lua_CFunction callable, Upvalues... upvalues)
{
    lua::push(state, upvalues...);
    lua_pushcclosure(state, callable, sizeof...(Upvalues));
    return lua::index(state, -1);
}

} // namespace lua

#endif // luacxx_convert_callable_INCLUDED
