# Understanding Userdata Memory

Luacxx's default userdata model is based on constructing C++ objects directly
inside Lua userdata and storing a small Luacxx metadata block alongside them.

This guide explains that memory model and why it is central to the library.

## Two Different Systems Meet Here

C++ usually prefers object lifetimes that are explicit and type-directed.
Lua uses garbage collection and a more dynamic runtime model.

When you expose a C++ object to Lua, something has to bridge those two worlds:

- Lua needs a userdata value it can retain and collect
- C++ needs a correctly-constructed object with a correct destructor

Luacxx bridges that gap by constructing C++ objects in Lua-managed memory.

## The Basic Pattern

At the raw Lua C API level, userdata allocation looks like this:

```cpp
void* block = lua_newuserdata(state, sizeof(Point));
new (block) Point();
```

That gives Lua ownership of the storage while still allowing C++ placement
construction of the object.

By default, the userdata is opaque. To make it usable from Lua, you normally
also provide a metatable with methods and a destruction path.

## What Luacxx Adds

Luacxx builds on the raw userdata model with:

- `lua::make<T>()` for in-place construction
- `lua::userdata_block` for metadata
- `lua::userdata_type` for runtime type information and cast support
- automatic `__gc` setup through the metatable machinery

So the real Luacxx layout is not just `sizeof(T)`. It is:

1. the object payload
2. a small metadata block after the payload

That metadata is what powers type checks, safe casts, and destruction.

## Value Userdata

When you push a value-like C++ object through the default userdata path, Luacxx
allocates userdata storage and constructs the object directly in it:

```cpp
Point p(2, 3);
lua::push(state, p);
```

If you want to pass constructor arguments directly, use `lua::make<T>()`:

```cpp
lua::make<Point>(state, 2, 3);
```

This is the standard Luacxx model for C++ objects that should live as userdata
values in Lua.

## Pointer Userdata

Luacxx can also store pointers in userdata rather than constructing a fresh
value object. In that case, the userdata metadata points at an existing C++
object instead of owning an in-place payload of type `T`.

That is useful when Lua should refer to an existing object rather than receive
its own copy.

## Destruction

The userdata metadata can store a destructor callback.

For value userdata, that destructor will usually call the C++ destructor for
the in-place object during Lua garbage collection. After destruction, Luacxx
clears the stored value pointer so repeated teardown paths can be detected.

This is one reason Luacxx can safely manage non-trivial C++ objects in Lua
userdata.

## Metatables Complete The Picture

A userdata becomes useful to Lua once it has a metatable.

Luacxx's metatable machinery wires in:

- `__gc`
- `__index`
- `__newindex`
- default `__tostring`

and lets `lua::Metatable<T>` specializations add methods and other metamethods.

That means the full userdata story is:

1. allocate storage
2. construct or attach the C++ object
3. record Luacxx metadata
4. attach a metatable
5. let Lua hold and eventually collect the value

## A Typical Class Constructor Binding

This is why a constructor binding often looks like this:

```cpp
int Point_new(lua_State* const state)
{
    if (lua_gettop(state) > 1) {
        lua::make<Point>(
            state,
            lua::get<int>(state, 2),
            lua::get<int>(state, 3)
        );
    } else {
        lua::make<Point>(state);
    }

    return 1;
}
```

Luacxx is constructing the actual `Point` in Lua-managed storage, not creating
an unrelated wrapper object around it.

## Why This Matters

This memory model is one of the reasons Luacxx can stay lightweight:

- no separate generator-produced wrapper layer is required
- C++ object layout is preserved
- destruction stays attached to the userdata lifecycle
- runtime type checks still remain available

## Related Docs

- [Binding a Class](binding-a-class.md)
- [Understanding Type Safety](understanding-type-safety.md)
- [Stack and Userdata](../reference/stack-and-userdata.md)
