# Working With The Lua Stack

Luacxx is built on top of Lua's C API, so the Lua stack still matters.

This is one of the library's core design choices: Luacxx gives you wrappers
and conversions, but it does not try to hide Lua's stack model completely.

If you understand how the Lua stack works, the rest of Luacxx tends to make a
lot more sense.

## The Basic Model

Most Lua C API operations work by pushing values onto a per-state stack and
then reading or rearranging them by index.

Typical patterns look like:

- push arguments
- call something
- read results
- clean up the stack

Indices can be:

- absolute, like `1` or `2`
- relative to the top, like `-1` for the topmost value

Luacxx keeps that model. It mostly gives you nicer ways to express the common
operations.

## What Luacxx Adds

The main stack-facing helpers are:

- `lua::push(...)`
- `lua::get<T>(state, pos)`
- `lua::store(destination, state, pos)`
- `lua::index`
- `lua::thread`

These all still operate on the current Lua stack.

For example:

```cpp
auto env = lua::create();

lua::push(env, 42);
int value = lua::get<int>(env, -1);
lua_pop(env, 1);
```

That is still ordinary Lua stack work. Luacxx is just handling the typed
conversion pieces.

## `lua::push(...)`

`lua::push(...)` is Luacxx's main way to place a value on the stack.

```cpp
auto pushed = lua::push(state, 42);
```

It does two things:

1. dispatches through `lua::Push<T>`
2. returns a `lua::index` pointing at the pushed value

That return value is one of the ways Luacxx makes stack-oriented code easier to
compose.

## `lua::get<T>(...)` And `lua::store(...)`

Reading from the stack usually goes through `lua::get<T>(state, pos)`:

```cpp
int number = lua::get<int>(state, 1);
std::string text = lua::get<std::string>(state, 2);
```

Writing into an existing C++ object goes through `lua::store(...)`:

```cpp
std::vector<int> values;
lua::store(values, state, 3);
```

These are just typed front-ends over the conversion templates:

- `lua::Push<T>`
- `lua::Store<T>`
- `lua::Get<T>`

## `lua::index`: A Stack Slot Wrapper

`lua::index` is the most direct Luacxx wrapper over the stack.

It stores:

- a `lua_State*`
- an absolute stack position

That makes it useful for:

- iterating over arguments
- holding onto a stack slot while pushing more values
- accessing `type()`, `operator[]`, and typed reads in a more object-like way

```cpp
for (lua::index arg(state, 1); arg; ++arg) {
    // inspect each stack slot
}
```

For a full walkthrough, see [Working With `lua::index`](working-with-index.md).

## `lua::thread`: A State Wrapper

`lua::thread` is a lightweight wrapper around `lua_State*`.

It is convenient when you want:

- `env["name"]` access to globals
- stream-style `env << value`
- a slightly more structured handle to the current state

But it still points at the same Lua stack underneath.

```cpp
auto env = lua::create();
env << 42 << "hello";
```

That code is still pushing two values onto the Lua stack.

## `lua::global` And `lua::link`

Not all Luacxx operations are direct stack-slot wrappers.

`lua::global` and `lua::link` represent symbolic access paths:

- `lua::global(state, "package")`
- `env["package"]["path"]`

They still use the stack internally when read or written, but they save you
from manually pushing tables and keys every time.

For that side of the API, see
[Working With `lua::global` And `lua::link`](working-with-global-and-link.md).

## `lua::reference`: When The Stack Is Not Enough

The stack is temporary. Once control returns to Lua or the stack is rearranged,
those slots are no longer a safe way to keep a value alive.

That is where `lua::reference` comes in.

It stores a value in Lua's registry so C++ can keep using it later without the
garbage collector reclaiming it.

Use it when:

- you need to save a callback
- you need to cache a Lua table
- you need a Lua value to survive past the current stack usage

For that workflow, see [Working With `lua::reference`](working-with-reference.md).

## A Typical Mixed Style

A lot of Luacxx code mixes raw Lua operations with Luacxx helpers:

```cpp
lua::push(state, lua::value::table);
auto table = lua::index(state, -1);

table["name"] = std::string("luacxx");
table["count"] = 42;

lua_setglobal(state, "config");
```

That is normal and intended. Luacxx is designed to cooperate with the Lua C
API rather than replace it.

## Good Rules Of Thumb

- use raw Lua functions when you need exact stack control
- use `lua::push`, `lua::get`, and `lua::store` for typed conversions
- use `lua::index` when you want to work directly with stack slots
- use `lua::global` and `lua::link` for symbolic table/global access
- use `lua::reference` when the value must survive beyond the current stack use

## Related Docs

- [Useful Lua Functions](useful-lua-functions.md)
- [Working With `lua::index`](working-with-index.md)
- [Working With `lua::global` And `lua::link`](working-with-global-and-link.md)
- [Working With `lua::reference`](working-with-reference.md)
- [Conversion Templates](conversion-templates.md)
