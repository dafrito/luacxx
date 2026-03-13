# Working With `lua::reference`

`lua::reference` is Luacxx's registry-backed handle for keeping a Lua value
alive while C++ holds onto it.

It is especially useful when:

- you need to save a Lua callback inside a C++ object
- you want to keep a Lua table around between calls
- you need a Lua value to survive after it leaves the stack

Unlike `lua::index`, a `lua::reference` is not just a view of a current stack
slot. It stores the value in the Lua registry, which prevents Lua's garbage
collector from reclaiming it while the reference exists.

## Why `lua::reference` Exists

Stack-based objects like `lua::index` are convenient, but they are temporary.
Once the stack changes, the value at that slot may change too.

`lua::reference` solves a different problem: "I need to keep this Lua value
around in C++ and use it later."

Typical examples include:

- storing a Lua function for later callbacks
- caching a Lua table in a C++ subsystem
- returning a Lua value from one part of your binding layer and using it later

## Basic Construction

You can create a reference from a state, a stack position, or another
Lua-facing value:

```cpp
lua::reference empty(state);
lua::reference from_stack(state, 1);
lua::reference from_global(lua::global(state, "package"));
```

Copying a `lua::reference` creates another registry reference to the same Lua
value. Each `lua::reference` owns its own registry slot and releases it in its
destructor.

## Saving A Lua Callback

This is one of the most common uses:

```cpp
struct Handler
{
    lua::reference callback;
};

int set_callback(lua_State* state)
{
    auto handler = lua::get<Handler*>(state, 1);
    handler->callback = lua::index(state, 2);
    return 0;
}

void fire(lua_State* state, Handler& handler)
{
    lua::call(handler.callback, 42);
}
```

The important part is that `handler.callback` keeps the Lua function alive even
after the original stack slot is gone.

## Reading Through A Reference

`lua::reference` supports the same style of typed access as other Luacxx
objects:

```cpp
std::string name = ref.get<std::string>();
int value = lua::get<int>(ref);
```

It also supports `operator[]`, which means you can navigate tables from a
saved reference:

```cpp
lua::reference package(lua::global(state, "package"));
std::string path = package["path"].get<std::string>();
```

## Assigning To A Reference

Assigning to a `lua::reference` replaces the value stored in its registry slot:

```cpp
lua::reference ref(state);
ref = 42;
ref = lua::global(state, "package");
ref = lua::index(state, 2);
```

Assigning `nil` releases the current registry value:

```cpp
ref = lua::value::nil;
```

Internally, `Store<lua::reference>` treats `nil` as "no referenced value" and
returns the reference to the empty state.

## Lifetime And Ownership

`lua::reference` is RAII-managed.

When a reference is destroyed, it calls `luaL_unref(...)` and releases its
registry slot.

That means:

- the referenced Lua value stays alive while the `lua::reference` exists
- once the last relevant reference is gone, Lua can collect the value normally

The reference does not copy the Lua value into C++. It keeps Lua ownership,
but pins the value in the registry.

## Empty References

A default-constructed or released `lua::reference` behaves like an empty
handle:

```cpp
lua::reference ref;
if (!ref) {
    // no referenced Lua value
}
```

An empty reference pushes `nil` when treated as a Lua value.

## How It Relates To Other Luacxx Types

- `lua::index` is a stack slot view
- `lua::global` is a named global lookup
- `lua::link` is a keyed lookup from another source
- `lua::reference` is a persistent registry-backed handle

If you only need to inspect a value already on the stack, `lua::index` is
usually enough.

If you need the value to survive after the current call or stack frame,
`lua::reference` is the right tool.

## Common Pattern: Return A Persistent Lua Value

Because `lua::reference` is a normal Luacxx conversion target, you can return
it from helpers that call Lua:

```cpp
lua::reference callable = lua::global(state, "make_handler")();
lua::call(callable, "hello");
```

This is often nicer than manually managing a stack result and immediately
converting it into a registry reference yourself.

## Related Docs

- [Working With `lua::index`](working-with-index.md)
- [Working With `lua::global` And `lua::link`](working-with-global-and-link.md)
- [Working With Callables](working-with-callables.md)
- [Understanding Type Safety](understanding-type-safety.md)
