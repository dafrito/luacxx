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

        env["AddDelta"] = lua::push_function<int(int)>([](int first) {
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

All this stuff involves calling C++ from Lua. This means pushing C++ functions
into Lua, and creating the infrastructure to invoke them reliably.

=head4 lua_CFunction, lua::function

The function type that can be called directly from Lua. As a result, these
can be pushed to Lua and will behave transparently as functions.

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

namespace {

struct ArgStop {};

template <typename Callee, typename RV, typename Arg, typename... Parameters>
struct Invoke
{
    template <typename... Arguments>
    static void invoke(const Callee& func, lua::index& index, Arguments... arguments)
    {
        /*static_assert(
                    // Non-references are fine
                    !std::is_reference<Arg>::value ||
                    // References to references are fine
                    std::is_reference<decltype(lua::get<Arg>(index++))>::value ||
                    // References to const are fine
                    std::is_const<typename std::remove_reference<Arg>::type>::value,
            "Provided function must not use non-const lvalue references to refer to temporary objects");*/
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

/*

=head2 class wrap_call<RV, Args...>

wrap_call is an internal tool for forwarding Lua values into a given C function
of arbitrary signature. The C function can have any signature as long as each
parameter is supported by this library. It's highly unlikely that you will
need to use this class directly.

This implementation was originally based off of
L<http://dvandyk.wordpress.com/2010/08/15/apply-functions-to-stdtuple/>

*/
template <typename RV, typename... Args>
class wrap_call
{
    /**
     * The C++ function that will eventually be invoked.
     */
    std::function<RV(Args...)> wrapped;

public:
    wrap_call(const std::function<RV(Args...)>& wrapped) :
        wrapped(wrapped)
    {}

    int operator()(lua::state* const state)
    {
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
};

} // namespace anonymous

/*

=head4 lua_pushcclosure(state, lua::function, int upvalues)

=head4 lua::push_closure(state, callable, upvalues...);

=head4 int lua_upvalueindex(int offset)

Returns the stack index that corresponds to the upvalue at the specified
offset. Upvalues are used to associate arbitrary Lua data with C functions,
but are rare to actually need in practice.

*/

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

template <typename RV, typename... Args>
struct Push<RV(*)(Args...)>
{
    static void push(lua::state* const state, RV(*func)(Args...))
    {
        lua::push(state, lua::callable(wrap_call<RV, Args...>(func)));
    }
};

template <typename RV, typename... Args>
struct Push<std::function<RV(Args...)>>
{
    static void push(lua::state* const state, const std::function<RV(Args...)>& func)
    {
        lua::push(state, lua::callable(wrap_call<RV, Args...>(func)));
    }
};

/*

=head4 lua::push_function<Signature>(state, callable)

*/

template <typename Signature>
static lua::index push_function(lua::state* const state, std::function<Signature> callable)
{
    return lua::push(state, callable);
}

/*

=head4 lua::push_closure(state, callable, upvalues...);

*/

template <typename... Upvalues>
static lua::index push_closure(lua::state* const state, lua::function callable, Upvalues... upvalues)
{
    lua::push(state, upvalues...);
    lua_pushcclosure(state, callable, sizeof...(Upvalues));
    return lua::index(state, -1);
}

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

} // namespace lua

#endif // LUA_CXX_TYPE_FUNCTION_HEADER
