# Metatable Macros

Luacxx provides a small set of macros for defining `lua::Metatable<T>`
specializations quickly.

These macros are the canonical shortcuts when you want a usable metatable
without writing the full specialization by hand.

## Why They Exist

A normal metatable specialization has two jobs:

1. provide runtime type information through `info()`
2. optionally populate the Lua metatable through `metatable(...)`

The macros cover the most common patterns:

- named types that need no custom metatable builder
- types with a custom builder function
- types that inherit from a base Luacxx userdata type

These macros are especially important because Luacxx does not enable automatic
fallback metatables by default. See [LUACXX_AUTO_METATABLE](luacxx-auto-metatable.md)
for the policy behind that choice.

## `LUA_METATABLE_NAMED(name)`

Use this when the type just needs a stable Luacxx type name and no custom
metatable-building logic.

```cpp
LUA_METATABLE_NAMED(MyType);
```

This expands to a `lua::Metatable<MyType>` specialization that:

- names the userdata `"MyType"`
- registers the type as castable to itself
- returns `true` from `metatable(...)` so the metatable can be cached
- does not add any custom methods or metamethods

This is a good default for simple userdata-bearing types, primitive wrappers,
and types whose default metatable behavior is sufficient.

Examples in the codebase include `std::string`, `lua::reference`, numeric
types, and several test-only types.

## `LUA_METATABLE_BUILT(name)`

Use this when you want a named type and a conventional builder function named
`name_metatable`.

```cpp
void MyType_metatable(lua_State* const state, const int mt);
LUA_METATABLE_BUILT(MyType);
```

This expands to a specialization that:

- names the userdata `"MyType"`
- registers the type as castable to itself
- calls `MyType_metatable(state, mt)` to populate the Lua metatable
- returns `true`, so the resulting metatable can be cached

This is useful when you want a short declaration and a separately-defined
builder function with the standard naming convention.

## `LUA_METATABLE_BUILT_WITH(name, builder)`

Use this when you want the same behavior as `LUA_METATABLE_BUILT`, but with an
explicit builder function name.

```cpp
void build_counter_metatable(lua_State* const state, const int mt);
LUA_METATABLE_BUILT_WITH(Counter, build_counter_metatable);
```

This expands to a specialization that:

- names the userdata `"Counter"`
- registers the type as castable to itself
- calls `build_counter_metatable(state, mt)`
- returns `true` so the metatable can be cached

This is handy when your builder function name does not follow the default
`Type_metatable` convention or when you want to reuse a differently-named
helper.

## `LUA_METATABLE_INHERIT(name, parent)`

Use this when the type should behave like a Luacxx userdata type that can also
be retrieved through a base class pointer.

```cpp
void Derived_metatable(lua_State* const state, const int mt);
LUA_METATABLE_INHERIT(Derived, Base);
```

This expands to a specialization that:

- names the userdata `"Derived"`
- registers `Derived` as castable to itself
- registers `Base` as a valid cast target from `Derived`
- calls `Derived_metatable(state, mt)`
- returns `true` so the metatable can be cached

This is the quick path for inheritance-aware metatables.

Because Luacxx records pointer offsets for registered base casts, this is the
macro to reach for when you want `lua::get<Base*>(...)` to work correctly for a
userdata that actually stores a `Derived`.

## When To Use A Manual `lua::Metatable<T>`

The macros are great for the common cases, but a hand-written specialization is
still the right choice when:

- the type name is dynamic or unusual
- metatable caching should be disabled
- you need more complex cast registration
- the metatable builder needs to inspect the object pointer
- the specialization should delegate to another type conditionally

In those cases, write `lua::Metatable<T>` yourself and use the macros as the
mental model for the baseline shape.

## Typical Choices

- Use `LUA_METATABLE_NAMED` for simple named types with no custom methods.
- Use `LUA_METATABLE_BUILT` when you have a standard `Type_metatable` builder.
- Use `LUA_METATABLE_BUILT_WITH` when the builder name should be explicit.
- Use `LUA_METATABLE_INHERIT` when the type should support base-class retrieval.

## Related Docs

- [Binding a Class](binding-a-class.md)
- [Understanding Type Safety](understanding-type-safety.md)
- [Stack and Userdata](../reference/stack-and-userdata.md)
