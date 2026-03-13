#ifndef luacxx_convert_callable_INCLUDED
#define luacxx_convert_callable_INCLUDED

#include <functional>
#include <sstream>

#include "../algorithm.hpp"
#include "../stack.hpp"
#include "../reference.hpp"

// Callable conversion and binding helpers. See
// docs/guide/working-with-callables.md for usage patterns and examples.

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

template <typename Object, typename... Args>
struct Push<void(Object::*)(Args...) const noexcept>
{
    static void push(lua_State* const state, void(Object::* func)(Args...) const noexcept)
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

template <typename RV, typename Object, typename... Args>
struct Push<RV(Object::*)(Args...) const noexcept>
{
    static void push(lua_State* const state, RV(Object::* func)(Args...) const noexcept)
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

template <typename Signature>
static lua::index push_function(lua_State* const state, std::function<Signature> callable)
{
    return lua::push(state, callable);
}

template <typename... Upvalues>
static lua::index push_closure(lua_State* const state, lua_CFunction callable, Upvalues... upvalues)
{
    lua::push(state, upvalues...);
    lua_pushcclosure(state, callable, sizeof...(Upvalues));
    return lua::index(state, -1);
}

} // namespace lua

#endif // luacxx_convert_callable_INCLUDED
