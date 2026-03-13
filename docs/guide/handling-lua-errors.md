# Handling `lua::error`

`lua::error` is Luacxx's main exception type for failures that occur while
working with Lua.

It is used for things like:

- Lua syntax errors
- Lua runtime errors
- type/conversion failures
- Luacxx API checks that are fundamentally about Lua values

## Why It Exists

Lua itself reports many failures through the C API and the Lua stack.
Luacxx converts those failures into a normal C++ exception type so they can be
handled with ordinary `try` / `catch`.

```cpp
try {
    lua::run_string(env, "error('Intentional')");
} catch (const lua::error& ex) {
    std::cerr << ex.what() << '\n';
}
```

## Message And Traceback

`lua::error` stores both the main message and, when available, a traceback.

The key methods are:

- `what()`
- `message()`
- `traceback()`
- `set_traceback(...)`

`what()` returns the full stored string. `message()` returns just the main
error text without the traceback suffix.

## Constructing One Yourself

You can throw a `lua::error` directly from C++ binding code:

```cpp
if (lua_type(state, 1) != LUA_TFUNCTION) {
    throw lua::error("A function was expected");
}
```

There is also a constructor that accepts a `lua_State*`, which Luacxx uses
when building richer messages from the current Lua context.

## What Should Throw `lua::error`

As a rule of thumb, `lua::error` is appropriate when the failure is naturally
part of using Lua:

- bad Lua code
- wrong Lua value type
- invalid Lua call target
- conversion failure

For purely host-side issues such as unrelated C++ logic failures, ordinary C++
exception types may still be more appropriate.

## Catching Errors Around Lua Calls

This is the common pattern:

```cpp
try {
    int answer = lua::call<int>(env["compute"], 2, 3);
} catch (const lua::error& ex) {
    std::cerr << "Lua call failed: " << ex.message() << '\n';
    if (!ex.traceback().empty()) {
        std::cerr << ex.traceback() << '\n';
    }
}
```

## Related Docs

- [Working With Callables](working-with-callables.md)
- [Loading And Running Lua Code](loading-and-running-lua-code.md)
- [Useful Lua Functions](useful-lua-functions.md)
