# Light Userdata And `void*`

Luacxx supports `void*` as a very narrow escape hatch for Lua light userdata.

This is intentionally limited.

## What Luacxx Does

In [`include/luacxx/convert/void.hpp`](/Users/aaronfaanes/Documents/luacxx/include/luacxx/convert/void.hpp):

- `lua::Push<void*>` pushes a pointer as Lua light userdata
- `lua::Store<void*>` only accepts Lua light userdata

That means this works:

```cpp
int value = 42;
void* ptr = &value;

lua::push(state, ptr);
void* round_trip = lua::get<void*>(state, -1);
```

## What Counts As Light Userdata

Light userdata is Lua's raw pointer type.

It is:

- just a pointer value
- not owned by Lua
- not garbage collected
- not associated with a metatable by Luacxx
- not a full userdata object

Luacxx maps `void*` only to that Lua light-userdata representation.

## What Does **Not** Convert To `void*`

Luacxx does **not** let you erase arbitrary Lua values into `void*`.

These do not convert to `void*`:

- full Luacxx userdata such as `Counter`, `Point`, `std::shared_ptr<T>`, or other C++ objects stored in userdata
- primitive Lua values such as numbers, strings, booleans, and tables

If you try to read one of those as `void*`, Luacxx throws `lua::error`.

That is intentional. Once a typed userdata has been reduced to `void*`, you
lose most of the type information and safety Luacxx is designed to preserve.

## Why Full Userdata Is Rejected

A Luacxx full userdata carries:

- runtime type information
- payload location
- destruction behavior
- cast rules

Treating that as an arbitrary `void*` would bypass the type-safety checks
described in [Understanding Type Safety](understanding-type-safety.md).

So Luacxx keeps those worlds separate:

- full userdata is for typed C++ objects
- light userdata is for raw pointers

## When `void*` Is Appropriate

Use `void*` only when you genuinely mean raw light userdata, for example:

- opaque tokens from a C API
- identity handles managed entirely outside Lua
- callback cookies or registry keys that are already pointer-shaped

If you want Lua to interact with a real C++ object, use userdata with a real
type and metatable instead.

## Rule Of Thumb

- Use `void*` for light userdata only.
- Use `lua::make<T>()`, `lua::get<T*>()`, and `lua::Metatable<T>` for actual C++ objects.
- Do not expect Luacxx full userdata or primitive Lua values to convert to `void*`.

## Related Docs

- [Understanding Type Safety](understanding-type-safety.md)
- [Understanding Userdata Memory](understanding-userdata-memory.md)
- [Conversion Templates](conversion-templates.md)
