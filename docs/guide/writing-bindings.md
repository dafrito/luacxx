# Writing Bindings

This guide preserves the original binding-writing guidance that shipped with
Luacxx. The repository no longer includes bundled third-party bindings, but the
advice still applies when using Luacxx to expose your own libraries.

## Synopsis

```cpp
#include <luacxx/thread.hpp>
#include <luacxx/convert/callable.hpp>
#include <luacxx/convert/numeric.hpp>

// http://cairographics.org/manual/cairo-cairo-device-t.html

void lua::cairo_device_t(lua_State* const state)
{
    lua::thread env(state);

    env["cairo_device_reference"] = cairo_device_reference;
    env["cairo_device_destroy"] = cairo_device_destroy;
    env["cairo_device_status"] = cairo_device_status;
    env["cairo_device_finish"] = cairo_device_finish;
    env["cairo_device_flush"] = cairo_device_flush;
}
```

## Keep The Original API Shape

Luacxx bindings should adhere to the original library's API wherever possible.
Do not casually rewrite naming conventions, method structure, or object
hierarchy. The ideal outcome is that the upstream library's own documentation
remains useful to the Lua user.

Write according to the public documentation, not just the source. Avoid binding
undocumented features unless they are essential to make the library usable.

If a binding grows beyond a single `hpp` and `cpp` pair, give it its own
directory and follow the original library's organization when practical.

## Deviate Only For Usability

Some APIs use patterns that Lua cannot reproduce elegantly, such as out
arguments or callbacks with pointer-heavy signatures. In those cases,
deviations are warranted, but they should be deliberate and consistent.

The goal is not strict literalism. The goal is a Lua-facing API that remains
recognizable while staying pleasant to use.

## Enumerations

C enumerations should usually be treated as integer constants. Do not invent a
new non-numeric representation just to make them look different in Lua.

Push and store support must be defined for enum classes if you want them to
round-trip cleanly:

```cpp
template<>
struct Push<QEvent::Type>
{
    static void push(lua_State* const state, const QEvent::Type& source)
    {
        lua_pushinteger(state, source);
    }
};

template<>
struct Store<QEvent::Type>
{
    static void store(QEvent::Type& destination, const lua::index& source)
    {
        destination = static_cast<QEvent::Type>(
            lua_tointeger(source.state(), source.pos())
        );
    }
};
```

## Structs

Structs should be constructible according to their documentation. Do not expose
undocumented constructors unless the type is clearly meant to be constructed
manually, such as a point or size struct.

Access to documented struct members should be provided via a metatable. If the
struct is intended to be opaque, only bind its documented public methods.

Do not turn C structs into C++-style object systems if the underlying library
does not do that itself.

## Objects

Objects should usually map to tables or userdata with a special metatable. Keep
member naming and casing aligned with the original API unless a Lua keyword
forces an alias.

If the object has a public constructor, prefer an explicit `new` method instead
of overloading `__call`. That avoids ambiguity with higher-order Lua helpers
such as partial application.

```lua
local curried = partial(Vector, "new", 50)
local vec = curried(50)
```

An explicit constructor call is easier to reason about than a table-level
`__call` convention.

## Pointers And Ownership

Ownership must be considered for every incoming and outgoing pointer.

Most pointers in C APIs do not imply ownership beyond the duration of the call.
Those functions can usually be bound directly. Avoid sprinkling in extra null
checks unless the upstream API requires them.

If a function returns a newly owned object, that lifecycle must be transferred
to Lua so the object can be destroyed correctly.

By convention, Luacxx can invoke a `destroy` method before garbage collection if
you provide one. During userdata teardown it may also invoke `free_userdata`.
Both of these should be idempotent if you implement them.

## Out Arguments As Placement Constructors

Pointer out-arguments are often really placement-constructor patterns in
disguise. When the callee does not retain the pointer and simply writes a
result, it can make sense to allocate and return that value from Lua instead of
forcing the caller to create it manually.

For example:

```c
cairo_bool_t cairo_recording_surface_get_extents(
    cairo_surface_t* surface,
    cairo_rectangle_t* extents
);
```

can be exposed in a Lua-friendly way by creating the rectangle implicitly when
the caller did not supply one:

```cpp
auto surface = lua::get<cairo_surface_t*>(state, 1);

if (lua::size(state) > 1) {
    auto extents = lua::get<cairo_rectangle_t*>(state, 2);
    lua::push(state, cairo_recording_surface_get_extents(surface, extents));
    return 1;
}

cairo_rectangle_t extents;
lua::push(state, cairo_recording_surface_get_extents(surface, extents));
return 2;
```

Do not be too aggressive with implicit arguments. Usually either none should be
provided, or all of them should be explicit.
