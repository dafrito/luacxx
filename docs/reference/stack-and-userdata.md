# Stack And Userdata

This page collects the larger narrative material that used to live in
`include/luacxx/stack.hpp`.

## Purpose

`stack.hpp` is where Luacxx defines the low-level facilities that sit closest
to Lua's stack and userdata model:

- stack inspection helpers such as `lua::dump`
- runtime type information for userdata
- userdata allocation and destruction
- metatable creation and caching
- pointer casting across supported userdata hierarchies

## Stack Model

Lua's C API is stack-based. Luacxx deliberately works with that model instead
of hiding it completely. In practice, that means:

- values are pushed to stage work
- indices identify stack values
- wrappers like `lua::index` and `lua::thread` make common patterns more
  convenient, but the underlying Lua behavior still matters

`lua::dump(state)` is primarily a debugging helper that provides a readable
description of the current stack.

## Userdata Memory Model

Luacxx pushes C++ objects as Lua userdata and stores a small metadata block
alongside them. That metadata tracks:

- the Luacxx type information
- the payload pointer
- destruction behavior

This lets Luacxx create C++ values in-place on Lua userdata and then destroy
them correctly during garbage collection.

Conceptually, the pattern looks like this:

```cpp
void* block = lua_newuserdata(state, sizeof(Point));
new (block) Point();
```

Luacxx automates that pattern through `lua::make<T>()` and the userdata helper
types in `stack.hpp`.

## `lua::userdata_type`

`lua::userdata_type` stores runtime information for a userdata type, including:

- its display name
- supported casts
- pointer offsets needed for inheritance-aware conversions

This is how Luacxx can check whether a userdata supports conversion to a given
requested type and perform the correct cast when inheritance is involved.

## `lua::userdata_block`

`lua::userdata_block` is the metadata header Luacxx places next to userdata
payloads. It tracks:

- the type info
- the payload address
- the destructor callback

This is also how Luacxx can mark a userdata as destroyed and avoid double
destruction.

## `lua::object_size`

`lua::object_size(state, pos)` returns the object payload size rather than the
raw userdata length. That matters because Luacxx appends metadata after the
payload.

## Metatables

Luacxx builds userdata metatables through `lua::Metatable<T>`.

Specializing `lua::Metatable<T>` lets you:

- name the userdata type
- register casts
- add methods or metamethods
- decide whether the metatable can be cached

The core workflow is:

1. provide `info()` with a stable name and casts
2. populate the metatable in `metatable(...)`
3. let Luacxx cache that metatable for future values of the same type

The builtin machinery also sets up:

- `__gc`
- `__index`
- `__newindex`
- default `__tostring`

## Allocation Helper

`lua::malloc(state, size)` allocates userdata storage sized for both the object
payload and Luacxx's metadata. Higher-level helpers such as `lua::make<T>()`
build on top of it.

## Related Docs

- [Useful Lua Functions](../guide/useful-lua-functions.md)
- [Thread And Algorithms](thread-and-algorithms.md)
