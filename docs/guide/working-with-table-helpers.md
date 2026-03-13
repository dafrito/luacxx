# Working With Table Helpers

Luacxx has a small set of helper functions in `lua::table` for common table
operations.

These are convenience functions layered on top of the same Lua table access
patterns you would otherwise write by hand.

## Main Helpers

The core helpers are:

- `lua::table::length(...)`
- `lua::table::insert(...)`
- `lua::table::get(...)`
- `lua::table::set(...)`
- `lua::table::get_type(...)`
- `lua::table::each(...)`
- `lua::table::call_each(...)`

There are also the aliases:

- `lua::setfield(...)`
- `lua::setglobal(...)`

## `lua::table::length`

Returns the length of a table-like Lua value.

```cpp
int n = lua::table::length(env["package"]["searchers"]);
```

This is mainly a wrapper over Lua's table length behavior.

## `lua::table::insert`

Appends a value at the end of an array-style Lua table:

```cpp
lua::table::insert(env["package"]["searchers"], my_searcher);
```

It computes the current length, then writes the new value at the next integer
key.

## `lua::table::get`

There are two useful forms.

Typed read:

```cpp
std::string path = lua::table::get<std::string>(env["package"], "path");
```

Stack-oriented read:

```cpp
lua::index path = lua::table::get(env["package"], "path");
```

The typed form leaves the stack as it found it. The `lua::index` form leaves
the looked-up value on the stack and returns a handle to it.

## `lua::table::set`

Writes a keyed value:

```cpp
lua::table::set(env["config"], "name", std::string("luacxx"));
```

This is roughly the helper equivalent of pushing a table, key, and value and
then calling `lua_settable(...)`.

## `lua::table::get_type`

This is a quick way to inspect the type of `source[key]` without first pulling
it into C++:

```cpp
auto t = lua::table::get_type(env["config"], "name");
if (t.string()) {
    // ...
}
```

## `lua::table::each`

Iterates across the array part of a table.

Typed callback:

```cpp
lua::table::each<int>(env["numbers"], [](int value) {
    // ...
});
```

Raw callback:

```cpp
lua::table::each(env["numbers"], [](lua_State* state, int pos) {
    // inspect state/pos manually
});
```

## `lua::table::call_each`

Treats each array entry as a callable and invokes it:

```cpp
lua::table::call_each(env["hooks"], "event-name");
```

This is a small convenience when a Lua table is acting as a list of callbacks.

## `lua::setfield` And `lua::setglobal`

`lua::setfield(...)` is just a thin alias for `lua::table::set(...)`.

`lua::setglobal(...)` pushes a value and writes it to a named global:

```cpp
lua::setglobal(env, "answer", 42);
```

## When To Use These Helpers

These helpers are most useful when:

- you want to stay in Luacxx style
- you are doing ordinary table work
- you want code that reads clearly without a lot of manual stack plumbing

If you need very specific low-level stack control, raw Lua API calls are still
the escape hatch.

## Related Docs

- [Working With `lua::global` And `lua::link`](working-with-global-and-link.md)
- [Working With `lua::index`](working-with-index.md)
- [Working With The Lua Stack](working-with-the-lua-stack.md)
