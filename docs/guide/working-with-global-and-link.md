# Working With `lua::global` And `lua::link`

`lua::global` and `lua::link` are both symbolic ways to talk about Lua
values without keeping them on the stack yourself.

They are similar in day-to-day use:

- both let you ask for `type()`
- both support `get<T>()`
- both support assignment
- both support `operator[]` for nested access

The difference is what they point at.

## `lua::global`

`lua::global` represents a named global in a particular `lua_State`.

```cpp
lua::global version(state, "VERSION");
std::string text = version.get<std::string>();
```

Assigning to a `lua::global` writes back through `lua_setglobal(...)`:

```cpp
lua::global answer(state, "answer");
answer = 42;
```

Reading from it pushes the current global value and converts it:

```cpp
int answer = lua::global(state, "answer").get<int>();
```

Use `lua::global` when you want to work with a top-level name such as
`package`, `math`, or your own application globals.

## `lua::link`

`lua::link<Source, Name>` represents a table-style access rooted at some other
Lua-facing object.

For example:

```cpp
auto loaded = lua::global(state, "package")["loaded"];
auto path = lua::global(state, "package")["path"];
```

Each `operator[]` creates another link, so nested access composes naturally:

```cpp
auto searchers = lua::global(state, "package")["searchers"];
auto first = searchers[1];
```

Under the hood, `lua::link` works by:

1. pushing its source
2. pushing its key
3. using `lua_gettable(...)` or `lua_settable(...)`

So it is a symbolic path to a value, not a cached reference to that value.

## A Simple Mental Model

You can think of them like this:

- `lua::global(state, "x")` means `_G["x"]`
- `some_link["y"]` means `some_link_value["y"]`

That is why they feel similar in use. A `lua::link` is often just “the next
step” after a `lua::global` or `lua::index`.

## Reading Values

For both types, `get<T>()` is the usual typed read:

```cpp
auto package_name = lua::global(state, "package")["config"].get<std::string>();
```

You can also use the streaming form:

```cpp
std::string path;
lua::global(state, "package")["path"] >> path;
```

Like elsewhere in Luacxx, these reads go through `lua::Get<T>` and
`lua::Store<T>`.

## Writing Values

Assignment writes through to Lua immediately:

```cpp
lua::global(state, "enabled") = true;
lua::global(state, "config")["name"] = std::string("luacxx");
```

Assigning one link to another copies the referenced Lua value through the
stack:

```cpp
auto src = lua::global(state, "defaults")["name"];
auto dst = lua::global(state, "config")["name"];
dst = src;
```

## Creating Links Explicitly

Most of the time you will just use `operator[]`:

```cpp
auto field = lua::global(state, "package")["path"];
```

There is also `lua::make_link(...)` if you want explicit construction and
template argument deduction:

```cpp
auto package = lua::global(state, "package");
auto path = lua::make_link(package, "path");
```

## How They Relate To `lua::index`

`lua::index`, `lua::global`, and `lua::link` form a small family:

- `lua::index` points at a stack slot
- `lua::global` points at a global name
- `lua::link` points at a keyed lookup from another Lua-facing object

They share a similar feel on purpose. In practice, `lua::link` is the bridge
that lets `lua::index`, `lua::global`, `lua::thread`, and similar types expose
table-style access with the same `operator[]` syntax.

## When To Use Which

- use `lua::global` when you are starting from a top-level Lua name
- use `lua::link` when you are navigating fields or elements from some other source
- use `lua::reference` when you need a persistent registry-backed Lua object
- use `lua::index` when you are working directly with the stack

## Related Docs

- [Working With `lua::index`](working-with-index.md)
- [Working With Strings](working-with-strings.md)
- [Working With Callables](working-with-callables.md)
