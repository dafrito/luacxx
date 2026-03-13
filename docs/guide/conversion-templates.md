# Conversion Templates

Luacxx's core customization model is built around four template structs:

- `lua::Push<T>`
- `lua::Store<T>`
- `lua::Get<T>`
- `lua::Construct<T>`

These are the extension points that teach Luacxx how a C++ type should move
between C++ and Lua.

## The Big Picture

Most of the user-facing helpers are thin wrappers around these templates:

- `lua::push(...)` dispatches to `lua::Push<T>`
- `lua::store(...)` dispatches to `lua::Store<T>`
- `lua::get<T>(...)` dispatches to `lua::Get<T>`
- `lua::make<T>(...)` dispatches to `lua::Construct<T>`

So when you customize one of these templates, you are changing how that type
behaves across a large portion of Luacxx.

## `lua::Push<T>`

`Push<T>` defines how a C++ value becomes a Lua value.

Conceptually:

```cpp
template <class T>
struct Push
{
    static void push(lua_State* const state, T value);
};
```

The default behavior in `stack.hpp` is userdata-oriented: Luacxx constructs a
userdata value for `T`.

You specialize `Push<T>` when a type should map to a different Lua
representation, such as:

- a number
- a string
- a table
- a callable
- a specialized userdata encoding

Examples in the codebase include:

- numeric types in [`include/luacxx/convert/numeric.hpp`](/Users/aaronfaanes/Documents/luacxx/include/luacxx/convert/numeric.hpp)
- strings in [`include/luacxx/convert/string.hpp`](/Users/aaronfaanes/Documents/luacxx/include/luacxx/convert/string.hpp)
- containers in [`include/luacxx/convert/vector.hpp`](/Users/aaronfaanes/Documents/luacxx/include/luacxx/convert/vector.hpp)

## `lua::Store<T>`

`Store<T>` defines how a Lua value is written into an existing C++ object.

Conceptually:

```cpp
template <class T>
struct Store
{
    static void store(T& destination, lua_State* const state, const int pos);
};
```

This is the “read from Lua into C++” path.

You specialize `Store<T>` when:

- the type has a non-default Lua representation
- the type should be rebuilt from a Lua table
- `nil` should have special meaning
- assignment should replace container contents in a custom way

Examples:

- `std::optional<T>` treats `nil` as reset in [`include/luacxx/convert/optional.hpp`](/Users/aaronfaanes/Documents/luacxx/include/luacxx/convert/optional.hpp)
- `std::vector<T>` rebuilds from a Lua array table in [`include/luacxx/convert/vector.hpp`](/Users/aaronfaanes/Documents/luacxx/include/luacxx/convert/vector.hpp)
- pointer retrieval uses userdata type checks in [`include/luacxx/stack.hpp`](/Users/aaronfaanes/Documents/luacxx/include/luacxx/stack.hpp)

## `lua::Get<T>`

`Get<T>` defines how a Lua value is returned as a C++ value.

Conceptually:

```cpp
template <class T>
struct Get
{
    static T get(lua_State* const state, const int pos);
};
```

The default `Get<T>` implementation usually constructs a destination object and
delegates to `Store<T>`.

That means you often only need to specialize `Store<T>`, not `Get<T>`.

You specialize `Get<T>` when:

- returning by value is more direct than default-construct-and-store
- the type should return a reference-like view
- the default `Store<T>`-based path is inefficient or awkward
- the type is callable or otherwise has a special retrieval path

Examples:

- `Get<T&>` and `Get<const T&>` in [`include/luacxx/stack.hpp`](/Users/aaronfaanes/Documents/luacxx/include/luacxx/stack.hpp)
- `Get<std::tuple<...>>` in [`include/luacxx/convert/tuple.hpp`](/Users/aaronfaanes/Documents/luacxx/include/luacxx/convert/tuple.hpp)
- `Get<std::function<...>>` in [`include/luacxx/convert/callable.hpp`](/Users/aaronfaanes/Documents/luacxx/include/luacxx/convert/callable.hpp)

## `lua::Construct<T>`

`Construct<T>` defines how Luacxx should create userdata for `T`.

Conceptually:

```cpp
template <class T>
struct Construct
{
    template <class... Args>
    static void construct(lua_State* const state, Args&&... args);
};
```

This is the low-level construction path that powers `lua::make<T>()` and the
default userdata-oriented `Push<T>`.

The built-in `Construct<T>`:

- allocates userdata storage
- records Luacxx type metadata
- placement-constructs the C++ object
- installs a destructor callback
- attaches the correct metatable

There are also built-in specializations for `T*` and `const T*`.

You usually do **not** need to specialize `Construct<T>` unless you are
changing how userdata should be created at a very low level.

Most custom types should specialize `Push<T>`, `Store<T>`, or `Get<T>` first.

## Which Luacxx APIs Use Them

Here is the practical dispatch map:

- `lua::push(state, value)` uses `lua::Push<T>::push(...)`
- `lua::store(destination, state, pos)` uses `lua::Store<T>::store(...)`
- `lua::store(destination, index)` also forwards to `Store<T>`
- `lua::get<T>(state, pos)` uses `lua::Get<T>::get(...)`
- `lua::get<T>(index)` also uses `Get<T>`
- `lua::make<T>(state, args...)` uses `lua::Construct<T>::construct(...)`

Higher-level helpers also build on these:

- `lua::call(...)` pushes arguments and gets return values through them
- `lua::thread` and `lua::global` assignments rely on `push`/`store`
- container conversions recursively use `push` and `store` for element types

## When You Usually Specialize Each One

- Specialize `Push<T>` when Lua should see a custom representation.
- Specialize `Store<T>` when Lua values should rebuild or assign into `T`.
- Specialize `Get<T>` when the default `Store<T>`-based retrieval is not the right fit.
- Specialize `Construct<T>` only when the default userdata construction model itself should change.

## Common Pattern

For many value-like types, this is enough:

```cpp
template <>
struct lua::Push<MyType>
{
    static void push(lua_State* const state, const MyType& source)
    {
        lua_pushinteger(state, source.value);
    }
};

template <>
struct lua::Store<MyType>
{
    static void store(MyType& destination, lua_State* const state, const int pos)
    {
        destination.value = lua::get<int>(state, pos);
    }
};
```

Then all of these start working naturally:

```cpp
lua::push(state, MyType{42});

MyType value{};
lua::store(value, state, 1);

MyType another = lua::get<MyType>(state, 1);
```

## A Useful Rule Of Thumb

Start at the highest-level customization point that matches your need.

- If you just need a custom Lua representation, start with `Push<T>` and `Store<T>`.
- If retrieval semantics are special, add `Get<T>`.
- If userdata construction itself is special, then consider `Construct<T>`.

That usually keeps your specializations simpler and lets the rest of Luacxx
reuse them automatically.

## Related Docs

- [Binding a Primitive Type](binding-a-primitive-type.md)
- [Binding a Class](binding-a-class.md)
- [Understanding Userdata Memory](understanding-userdata-memory.md)
- [Stack and Userdata](../reference/stack-and-userdata.md)
