#ifndef LUA_CXX_TYPE_FUNCTION_HEADER
#define LUA_CXX_TYPE_FUNCTION_HEADER

#include <functional>
#include <sstream>

#include "algorithm.hpp"
#include "state.hpp"
#include "exception.hpp"
#include "stack.hpp"

// All this stuff involves calling C++ from Lua. This means pushing C++
// functions into Lua, and creating the infrastructure to invoke them reliably.

namespace {

struct ArgStop {};

template <typename Callee, typename RV, typename Arg, typename... Remaining>
struct Invoke
{
    template <typename... Rest>
    static void invoke(lua::index& index, const Callee& func, Rest... rest)
    {
        static_assert(
                    // Non-references are fine
                    !std::is_reference<Arg>::value ||
                    // References to references are fine
                    std::is_reference<decltype(lua::get<Arg>(index++))>::value ||
                    // References to const are fine
                    std::is_const<typename std::remove_reference<Arg>::type>::value,
            "Provided function must not use non-const lvalue references to refer to temporary objects");
        Invoke<Callee, RV, Remaining...>::template invoke<Rest..., Arg>(
            index, func, rest..., lua::get<Arg>(index++)
        );
    }
};

template <typename Callee, typename RV>
struct Invoke<Callee, RV, ArgStop>
{
    template <typename... FullArgs>
    static void invoke(lua::index& index, const Callee& func, FullArgs... args)
    {
        lua::clear(index.state());
        lua::push(index.state(), func(args...));
    }
};

template <typename Callee>
struct Invoke<Callee, void, ArgStop>
{
    template <typename... FullArgs>
    static void invoke(lua::index& index, const Callee& func, FullArgs... args)
    {
        lua::clear(index.state());
        func(args...);
    }
};

/**
 * LuaWrapper enables C++ functions of arbitrary complexity to be called
 * from Lua. Conceptually, the template behaves similarly to a varargs
 * function from C. However, types are preserved using variadic templates.
 * This allows us to automatically generate correct code for each
 * argument.
 *
 * This implementation was based off of:
 * http://dvandyk.wordpress.com/2010/08/15/apply-functions-to-stdtuple/
 */
template <typename RV, typename... Args>
class wrap_call
{
    /**
     * The C++ function that will eventually be invoked.
     */
    std::function<RV(Args...)> wrapped;

public:
    wrap_call(std::function<RV(Args...)> wrapped) :
        wrapped(wrapped)
    {}

    int operator()(lua::state* const state)
    {
        #pragma clang diagnostic push
        #pragma clang diagnostic ignored "-Wtautological-compare"
        if (lua::size(state) < sizeof...(Args)) {
        #pragma clang diagnostic pop
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
            throw lua::exception(msg.str());
        }

        lua::index arg(state, 1);
        Invoke<decltype(wrapped), RV, Args..., ArgStop>::template invoke<>(arg, wrapped);
        return 1;
    }
};

} // namespace anonymous

namespace lua {

typedef lua_CFunction function;
typedef std::function<int(lua::state* const)> callable;

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
    } catch (lua::exception& ex) {
        lua::push(state, ex);
        lua_error(state);
        throw std::runtime_error("lua_error should throw");
    }
}

template <>
struct Push<lua::callable>
{
    static void push(lua::state* const state, const lua::callable& callable)
    {
        lua::push_userdata(state, callable);
        lua_pushcclosure(state, invoke_callable, 1);
    }
};

template <>
struct Store<lua::callable>
{
    static void store(lua::callable& destination, const lua::index& source)
    {
        lua_getupvalue(source.state(), source.pos(), 1);
        lua::store_userdata(destination, lua::index(source.state(), -1));
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

template <typename Function>
static lua::index push_function(lua::state* const state, std::function<Function> callable)
{
    return lua::push(state, callable);
}

} // namespace lua

/*

// Raw LuaCallables that return useful values
template <class RV,
    typename std::enable_if<!std::is_same<RV, void>::value, int>::type = 0>
void push(LuaStack& stack, RV (*p)(LuaStack&), const int closed = 0)
{
    //std::cout << "Pushing raw LuaCallable with return value" << std::endl;
    lua::push(stack, lua::LuaCallable([=](LuaStack& stack) {
        RV sink(p(stack));
        stack.clear();
        lua::push(stack, sink);
    }), closed);
}

// C++ LuaCallables that return useful values
template <class RV,
    typename std::enable_if<!std::is_same<RV, void>::value, int>::type = 0>
void push(LuaStack& stack, std::function<RV(LuaStack&)> func, const int closed = 0)
{
    //std::cout << "Pushing std::function LuaCallable with return value" << std::endl;
    lua::push(stack, lua::LuaCallable([=](LuaStack& stack) {
        RV sink(func(stack));
        stack.clear();
        lua::push(stack, sink);
    }), closed);
}

*/

#endif // LUA_CXX_TYPE_FUNCTION_HEADER
