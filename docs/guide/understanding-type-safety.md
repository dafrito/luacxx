# Understanding Type Safety

Luacxx does not trust a raw `lua_touserdata()` pointer by itself.

When Luacxx stores a C++ object in Lua userdata, it also stores Luacxx-specific
metadata describing:

- what C++ type the userdata holds
- where the object payload lives
- how to destroy it
- what casts are valid from that concrete type

That metadata is what lets Luacxx check whether a requested C++ type actually
matches the userdata on the Lua stack.

## The Core Idea

Every Luacxx userdata has two parts:

1. the payload, which is the C++ object or pointer being exposed
2. a trailing `lua::userdata_block`, which stores the type information

When Luacxx allocates userdata through `lua::malloc(...)`, it reserves space
for both pieces. When a value is constructed with `lua::make<T>()` or pushed
through the default userdata path, the block is initialized with:

- a pointer to `lua::Metatable<T>::info()`
- the payload address
- an optional destructor callback

So later, when code asks for `lua::get<MyType*>(state, pos)`, Luacxx is not
guessing. It is consulting the stored metadata.

## Runtime Type Information

The type metadata lives in `lua::userdata_type`.

Each `lua::userdata_type` contains:

- a stable type name
- a list of allowed casts
- the pointer offset for each cast

The normal source of this info is `lua::Metatable<T>::info()`.

For a simple type, that usually looks like:

```cpp
static const lua::userdata_type& info()
{
    static lua::userdata_type type("Counter");
    if (!type.has_casts()) {
        type.add_cast<Counter>();
    }
    return type;
}
```

That says: this userdata is a `Counter`, and it may be viewed as a `Counter`.

## How Retrieval Works

For pointer retrieval, the path is roughly:

1. get the userdata block from the Lua stack slot
2. ask the block to cast to the requested type
3. verify that the cast is registered
4. apply the stored pointer offset
5. return the typed pointer

In code, `Store<T*>` eventually does this:

```cpp
auto block = lua::get_userdata_block(state, pos);
destination = block->cast<T>(state);
```

And `block->cast<T>(state)` eventually checks the userdata's stored
`lua::userdata_type` against `lua::Metatable<T>::info()`.

If the cast is not valid, Luacxx throws `lua::error` instead of returning an
invalid pointer.

## Inheritance Support

Luacxx can also support safe base-class conversions.

When you register casts such as:

```cpp
type.add_cast<Derived>();
type.add_cast<Base, Derived>();
```

Luacxx records the pointer offset from `Derived*` to `Base*`. That matters for
multiple inheritance, where a base subobject may not begin at offset zero.

In practice, that registration usually happens in the type's metatable info.
For example:

```cpp
template <>
struct lua::Metatable<Derived>
{
    static const lua::userdata_type& info()
    {
        static lua::userdata_type type("Derived");
        if (!type.has_casts()) {
            type.add_cast<Derived>();
            type.add_cast<Base, Derived>();
        }
        return type;
    }
};
```

Luacxx also provides helper macros such as `LUA_METATABLE_INHERIT(name, parent)`
for this common pattern.

When the userdata is later requested as `Base*`, Luacxx:

- verifies that `Base` is a registered cast target
- adds the recorded offset to the stored payload pointer
- returns the adjusted pointer

So this is not just “same name means OK.” It is a checked runtime cast table
with offset-aware pointer adjustment.

That means code like this is supported when the cast was registered:

```cpp
Derived* derived = lua::get<Derived*>(state, 1);
Base* base = lua::get<Base*>(state, 1);
```

Both retrievals refer to the same underlying userdata, but the `Base*` path may
apply an offset before returning the pointer.

## Why Not Just Use `lua_touserdata()`?

Plain `lua_touserdata()` only tells you that a stack slot contains userdata.
It does not tell you:

- which C++ type it holds
- whether the value was created by Luacxx
- whether the requested cast is valid
- whether the object has already been destroyed

Luacxx's metadata layer adds that missing information.

## Destroyed Userdata

The userdata block also tracks whether a value still exists.

During destruction, Luacxx runs the stored destructor and then clears the value
pointer. That lets Luacxx and some internal callers detect that the userdata
has already been torn down and avoid using a dead object.

## Shared Ownership And Pointers

Different userdata storage strategies still go through the same type-info path.

- value userdata stores an in-place C++ object
- pointer userdata stores a raw pointer value
- `std::shared_ptr<T>` userdata preserves shared ownership semantics

Luacxx is intentionally conservative about unsafe erasure. For example,
shared-pointer userdata is not treated as safely convertible to `void*`.

## Practical Rule

Luacxx's type safety for userdata comes from three checks working together:

1. the userdata must actually be Luacxx userdata
2. the userdata must carry matching `lua::userdata_type` information
3. the requested type must be present in the registered cast set

If any of those assumptions fail, retrieval throws instead of silently handing
back the wrong C++ type.

## Related Docs

- [Binding a Class](binding-a-class.md)
- [Working With shared_ptr](working-with-shared-ptr.md)
- [Stack and Userdata](../reference/stack-and-userdata.md)
