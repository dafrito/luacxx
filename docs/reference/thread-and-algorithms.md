# Thread And Algorithms

This page pulls together the higher-level usage notes that used to be spread
across `thread.hpp` and `algorithm.hpp`.

## `lua::thread`

`lua::thread` is a lightweight C++ wrapper around `lua_State*`.

Its main jobs are:

- provide convenient global access through `env["name"]`
- optionally own the underlying Lua state
- convert back to `lua_State*` when you need to call raw Lua APIs

Typical usage:

```cpp
int luaopen_Foo(lua_State* const state)
{
    lua::thread env(state);
    env["Foo"] = lua::value::table;
    return 0;
}
```

`lua::create()` constructs a new state with standard libraries and returns a
`lua::thread` that owns it by default.

## Common Algorithms

`algorithm.hpp` contains the convenience helpers that tie the rest of the
library together.

Important ones include:

- `lua::dump(state)` for stack diagnostics
- `lua::memory_address(index)` for readable identity/debug output
- `lua::assert_type` for better type errors
- `lua::top`, `lua::size`, `lua::clear`, `lua::remove`, and `lua::swap`
- `lua::store` and `lua::get` for generic conversion through `Store<T>` and
  `Get<T>`
- `lua::make<T>` for userdata construction
- `lua::get_all` for collecting stack values into a `std::vector`

## Calling Lua From C++

Luacxx provides two main helpers here:

- `lua::invoke(...)`
- `lua::call<RV>(...)`

`invoke` executes a callable already present on the Lua stack. `call` is the
higher-level helper that:

1. pushes the callable and arguments
2. invokes it
3. converts the result back to C++
4. restores the stack shape for you

These helpers are meant to coexist with raw Lua API calls, not replace them in
every situation.

## Constructing Userdata

`lua::make<T>(state, args...)` constructs a userdata value of type `T` directly
on the Lua stack. That is the usual Luacxx path for exposing C++ objects to
Lua while preserving native object layout and destruction semantics.
