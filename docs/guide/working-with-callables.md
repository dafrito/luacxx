# Working With Callables

Luacxx can move several kinds of C++ callables into and out of Lua:

- raw `lua_CFunction`
- ordinary function pointers
- member function pointers
- `std::function`
- lambdas, usually through `std::function` or `lua::push_function`

This is one of the places where Luacxx benefits a lot from variadic templates:
typed arguments and return values can be marshalled without writing a custom
wrapper for every arity.

## The Two Main Styles

There are two broad ways to bind callables:

1. raw Lua-stack style
2. typed argument style

### Raw Lua-Stack Style

This is the classic Lua C API shape:

```cpp
int my_function(lua_State* const state)
{
    int a = lua::get<int>(state, 1);
    int b = lua::get<int>(state, 2);
    lua::push(state, a + b);
    return 1;
}
```

This style gives you full control over the stack and is a good fit when:

- the function already thinks in Lua stack terms
- you need varargs
- you want fine-grained control over return counts
- you are wrapping lower-level Lua runtime behavior

### Typed Argument Style

This is the higher-level Luacxx path:

```cpp
int add(int a, int b)
{
    return a + b;
}

lua::push(state, add);
```

Here Luacxx reads the Lua arguments, calls the C++ function, and pushes the
result for you.

This is a good fit when:

- the callable has a fixed signature
- the arguments and return type already have Luacxx conversions
- you want the C++ side to look like ordinary C++ code

## Raw `lua_CFunction`

Luacxx supports Lua's native C function type directly:

```cpp
int add_from_stack(lua_State* const state)
{
    int a = lua::get<int>(state, 1);
    int b = lua::get<int>(state, 2);
    lua::push(state, a + b);
    return 1;
}

env["add"] = add_from_stack;
```

This ends up as a Lua C closure.

Luacxx also supports storing and retrieving `lua_CFunction` values.

## Ordinary Function Pointers

Typed free functions can be pushed directly:

```cpp
int add(int a, int b)
{
    return a + b;
}

env["add"] = add;
```

When Lua calls `add(2, 3)`, Luacxx:

1. converts Lua arguments to `int, int`
2. calls `add`
3. pushes the returned `int`

This works as long as the argument and return types have conversions.

## Member Function Pointers

Member functions work too:

```cpp
struct Counter
{
    void add(int amount);
    int get() const;
};

mt["add"] = &Counter::add;
mt["get"] = &Counter::get;
```

Luacxx treats these like functions whose first argument is the object pointer,
so they fit naturally into userdata-backed metatables.

This is one of the nicest parts of the callable support, because it lets class
bindings look close to the C++ API.

## `std::function`

Luacxx can also push `std::function<RV(Args...)>` directly:

```cpp
env["multiply"] = std::function<int(int, int)>(
    [](int a, int b) {
        return a * b;
    }
);
```

This is especially useful when:

- you want to capture state in a lambda
- you want a uniform callable type on the C++ side
- you want to build a callable dynamically

Luacxx also supports retrieving `std::function<...>` back from Lua.

## `lua::push_function`

`lua::push_function` is a convenient way to push lambdas with an explicit
signature:

```cpp
auto pushed = lua::push_function<int(int, int)>(env, [](int a, int b) {
    return a + b;
});

env["Adder"] = pushed;
```

This is often the nicest way to bind an inline lambda without spelling out a
`std::function<...>` variable first.

## `lua::callable`

`lua::callable` is Luacxx's wrapper for raw Lua-state-style callables:

```cpp
env["thrower"] = lua::callable([](lua_State* const) -> int {
    throw lua::error("Intentional");
});
```

This is useful when you still want raw stack control, but prefer to package the
callable as a C++ function object instead of a plain `lua_CFunction`.

## Calling Lua From C++

The same callable support also helps on the way back from Lua to C++.

The main helpers are:

- `lua::invoke(...)`
- `lua::call<RV>(...)`

Example:

```cpp
lua::run_string(env,
    "function add(a, b)\n"
    "  return a + b\n"
    "end");

int result = lua::call<int>(env["add"], 2, 3);
```

`lua::call` pushes the callable and arguments, performs the Lua call, converts
the result, and returns it as C++.

## Strictness

Callable support is only as strong as the conversions for the involved types.

That means:

- arguments must be convertible from Lua to the C++ parameter types
- return values must be pushable back to Lua
- method pointers rely on the userdata object being retrievable as the correct C++ type

If a type does not have the right Luacxx conversion, the callable binding will
fail at compile time or throw during conversion.

## When To Use Which Form

- Use `lua_CFunction` or `lua::callable` when you want direct stack control.
- Use ordinary function pointers for the cleanest typed binding style.
- Use member function pointers inside metatables for class methods.
- Use `std::function` or `lua::push_function` for lambdas and runtime-created callables.

## Related Docs

- [Binding a Class](binding-a-class.md)
- [Conversion Templates](conversion-templates.md)
- [Thread and Algorithms](../reference/thread-and-algorithms.md)
