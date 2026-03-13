# Working With `lua::index`

`lua::index` is Luacxx's lightweight wrapper around a Lua stack position.

It gives you a more object-oriented way to work with stack values without
hiding the underlying Lua stack model.

## What It Represents

A `lua::index` stores:

- a `lua_State*`
- an absolute stack position

Because the position is made absolute up front, the index remains stable even
if you later push more values onto the stack.

It is still a stack handle, not a persistent Lua reference. If the value at
that stack slot is removed or replaced, the `lua::index` will observe the new
state of that slot.

## Basic Construction

```cpp
lua::index value(state, 1);
lua::index top_value(state, -1);
```

The constructor immediately normalizes the position with `lua_absindex(...)`.

## Basic Access

The main accessors are:

- `index.state()`
- `index.pos()`
- `index.type()`

Example:

```cpp
lua::index value(state, 1);
if (value.type().string()) {
    std::string text = lua::get<std::string>(value);
}
```

## Iterating Over The Stack

`lua::index` behaves a bit like a smart pointer over stack positions:

- `operator bool()` tells you whether the position is still in range
- `++index` and `--index` move to adjacent positions

That makes it convenient for stack iteration:

```cpp
int sum = 0;
for (lua::index value(state, 1); value; ++value) {
    sum += lua::get<int>(value);
}
```

## Reading A Typed Value

There are two main ways to read through a `lua::index`.

For a non-consuming read, use the free `lua::get<T>(index)` helper:

```cpp
lua::index value(state, 1);
int number = lua::get<int>(value);
```

This is the usual choice when you are reading function arguments or iterating
over existing stack slots.

`index.get<T>()` is a more specialized helper. It reads from the indexed slot
and then pops one value from the top of the stack:

```cpp
auto pushed = lua::push(state, 42);
int number = pushed.get<int>();
```

That makes it a good fit for values that were just pushed or loaded onto the
top of the stack, but not for arbitrary stack traversal.

## Replacing A Stack Value

Assigning to a `lua::index` replaces the value at that stack slot:

```cpp
lua::index target(state, 1);
target = 42;
```

This works by pushing the new value and then `lua_replace(...)`-ing the stack
slot at `target.pos()`.

You can also assign another Lua-facing value:

```cpp
lua::index first(state, 1);
lua::index second(state, 2);
first = second;
```

## Table-Style Access

`operator[]` creates a `lua::link` rooted at this stack value:

```cpp
lua::index table(state, 1);
int id = table["id"].get<int>();
```

This does not immediately modify the stack. It gives you a convenient way to
work with fields and elements relative to the indexed value.

## Streaming Out Of The Stack

`operator>>` stores the current value into a C++ destination and then advances
the index:

```cpp
lua::index value(state, 1);

int a;
int b;
value >> a >> b;
```

This is handy when reading a sequence of arguments.

## `lua::push` And `lua::index`

Luacxx's `lua::push(...)` helpers return a `lua::index` to the topmost pushed
value:

```cpp
auto table = lua::push(state, lua::value::table);
table["answer"] = 42;
```

That makes `lua::index` one of the main glue types for stack-oriented code.

There is also a `Push<lua::index>` specialization, which means pushing an
index pushes a copy of the referenced Lua value.

The same pattern shows up in helpers like `lua::load_string(...)` and
`lua::load_file(...)`, which return a `lua::index` for the loaded chunk.

## When To Use `lua::index`

`lua::index` is especially useful when:

- you are iterating over stack values
- you want to keep a stable handle to a stack slot
- you want object-style access to `type()`, `get<T>()`, and `operator[]`
- you are writing low-level binding code that still wants some structure

As a rule of thumb:

- use `lua::get<T>(index)` for ordinary typed reads
- use `index >> destination` for sequential extraction
- use `index.get<T>()` when the indexed value is also the top value you want to consume

If you are working with globals or longer-lived values, `lua::global`,
`lua::reference`, and `lua::thread` may be a better fit.

## Related Docs

- [Useful Lua Functions](useful-lua-functions.md)
- [Conversion Templates](conversion-templates.md)
- [Thread and Algorithms](../reference/thread-and-algorithms.md)
