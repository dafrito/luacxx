# Working With `lua::value`

`lua::value` is a small enum used for pushing a few Lua-specific values that
do not naturally come from ordinary C++ objects.

It is mainly a convenience for places where you want to say "push a fresh Lua
table" or "push `nil`" using the normal Luacxx `lua::push(...)` path.

## What It Covers

The built-in `lua::value` entries are:

- `lua::value::nil`
- `lua::value::table`
- `lua::value::globals`
- `lua::value::thread`
- `lua::value::registry`

They all work through the `Push<lua::value>` specialization in
[`include/luacxx/value.hpp`](/Users/aaronfaanes/Documents/luacxx/include/luacxx/value.hpp).

## Common Uses

The most common use is creating a table:

```cpp
env["config"] = lua::value::table;
env["config"]["name"] = std::string("luacxx");
```

You can also explicitly push one:

```cpp
auto table = lua::push(state, lua::value::table);
table["answer"] = 42;
```

Setting something to `nil` is another common pattern:

```cpp
env["current_task"] = lua::value::nil;
```

That is especially handy when removing a global or table field.

## How Each Entry Maps To Lua

- `lua::value::nil`
  Pushes Lua `nil` with `lua_pushnil(...)`.

- `lua::value::table`
  Pushes a fresh empty table with `lua_newtable(...)`.

- `lua::value::globals`
  Pushes the global environment table with `lua_pushglobaltable(...)`.

- `lua::value::thread`
  Pushes a new Lua thread with `lua_newthread(...)`.

- `lua::value::registry`
  Pushes the registry table with `lua_pushvalue(state, LUA_REGISTRYINDEX)`.

## Why Use This Instead Of Raw Lua Calls

`lua::value` is useful when you want to stay in the Luacxx style:

- `env["name"] = lua::value::table`
- `auto globals = lua::push(state, lua::value::globals)`
- `ref = lua::value::nil`

That keeps the code readable and works smoothly with `lua::index`,
`lua::global`, `lua::link`, and `lua::reference`.

If you need something more specific than these built-in Lua values, the raw Lua
C API is still the right escape hatch.

## What `lua::value` Is Not

`lua::value` is not a general tagged Lua object type.

It does not represent arbitrary existing Lua values. It is just a small set of
instructions for pushing special Lua-side values onto the stack.

If you already have a real Lua value, you probably want one of these instead:

- `lua::index` for a stack slot
- `lua::global` for a named global
- `lua::link` for a field or element lookup
- `lua::reference` for a persistent registry-backed handle

## Related Docs

- [Working With `lua::index`](working-with-index.md)
- [Working With `lua::global` And `lua::link`](working-with-global-and-link.md)
- [Working With `lua::reference`](working-with-reference.md)
- [Useful Lua Functions](useful-lua-functions.md)
