# `LUACXX_AUTO_METATABLE`

`LUACXX_AUTO_METATABLE` changes one of Luacxx's most important policies:
whether an otherwise-unsupported C++ type should be accepted as userdata by
default.

By default, this macro is **not** enabled.

That default is intentional.

## Default Behavior: No Implicit Metatable

When `LUACXX_AUTO_METATABLE` is not defined, the primary `lua::Metatable<T>`
template does not provide a fallback implementation.

That means a type must have an explicit metatable specialization before Luacxx
can use it as userdata. In practice, that usually means one of:

- a hand-written `lua::Metatable<T>` specialization
- a metatable macro such as `LUA_METATABLE_NAMED(...)`
- including a Luacxx header that already defines the metatable for the type

If no such metatable exists, compilation fails.

This is usually a good failure mode. In many real cases, the programmer simply
forgot to include the header that defines the metatable or conversion they
meant to use.

## Why The Strict Default Is Useful

Without the strict default, a missing include can silently turn into “the code
compiled, but the value behaves like a generic userdata in Lua.”

That is often worse than a compile error, because:

- the real bug is hidden
- Lua code sees an opaque object instead of the intended methods or behavior
- inheritance registrations and custom casts may be missing
- the type may appear to work at first while still being semantically wrong

So the default behavior is designed to catch integration mistakes early.

## What Happens When It Is Enabled

When `LUACXX_AUTO_METATABLE` is defined, Luacxx provides a fallback
`lua::Metatable<T>` for otherwise-unsupported types.

That fallback:

- gives the type the generic name `"anonymous userdata"`
- registers the type as castable to itself
- returns `true` from `metatable(...)`
- does not add any type-specific methods or metamethods

One important nuance: Luacxx still creates a metatable table in this mode. So
the userdata is not literally “without a metatable.” Instead, it gets only the
generic Luacxx-managed metatable behavior, such as `__gc`, `__index`,
`__newindex`, and default `__tostring`, but no type-specific API.

In practice, that usually means the value behaves like opaque userdata from
Lua's point of view.

## Why This Can Be Misleading

`LUACXX_AUTO_METATABLE` can make missing metatable definitions much harder to
notice.

A type that should have had a real metatable may instead:

- compile successfully
- be pushed into Lua as userdata
- expose no useful methods
- carry only the generic `"anonymous userdata"` identity

That can look like a runtime bug in the binding, when the real problem is just
that the proper metatable definition was never included.

## Inheritance Implications

This fallback does **not** automatically reuse a parent class metatable.

If you push a `Derived` type with `LUACXX_AUTO_METATABLE` enabled and there is
no explicit `lua::Metatable<Derived>`, Luacxx uses the generic fallback for
`Derived`. It does not infer that `Derived` should behave like `Base`, and it
does not automatically register base-class casts.

That means:

- `lua::get<Derived*>(...)` can still work for the exact fallback type
- `lua::get<Base*>(...)` will not work unless the base cast was explicitly
  registered
- inherited methods from a parent metatable are not picked up automatically

So if inheritance matters, you should still define the real metatable, usually
with a manual specialization or `LUA_METATABLE_INHERIT(...)`.

## Recommended Use

Treat `LUACXX_AUTO_METATABLE` as a deliberate compatibility or experimentation
mode, not as the normal way to fix missing metatable errors.

Good reasons to use it:

- you are exploring a codebase and want unsupported values to compile
- you intentionally want generic opaque userdata behavior
- you are testing low-level userdata storage without binding methods yet

Poor reasons to use it:

- to suppress a compile error caused by a missing metatable include
- to “make the type work” when what you really want is a richer Lua API
- to paper over missing inheritance registration

If your Lua value is supposed to have methods, names, casts, or inheritance
behavior, the better fix is usually to define or include the correct
`lua::Metatable<T>`.

## Related Docs

- [Metatable Macros](metatable-macros.md)
- [Understanding Type Safety](understanding-type-safety.md)
- [Binding a Class](binding-a-class.md)
