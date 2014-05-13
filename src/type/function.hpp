#ifndef LUA_CXX_TYPE_FUNCTION_HEADER
#define LUA_CXX_TYPE_FUNCTION_HEADER

#include <functional>
#include <sstream>

#include "algorithm.hpp"
#include "state.hpp"
#include "error.hpp"
#include "push.hpp"
#include "store.hpp"

// All this stuff involves calling C++ from Lua. This means pushing C++
// functions into Lua, and creating the infrastructure to invoke them reliably.

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
    wrap_call(const std::function<RV(Args...)>& wrapped) :
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
            throw lua::error(msg.str());
        }

        lua::index index(state, 1);
        Invoke<decltype(wrapped), RV, Args..., ArgStop>::template invoke<>(wrapped, index);
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
