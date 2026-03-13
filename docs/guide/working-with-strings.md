# Working With Strings

Luacxx's preferred string type is `std::string`.

That is the main owned string type for reading values back from Lua, and it is
usually the right choice for binding APIs as well.

## The Main Rule

- Use `std::string` when you want to read strings from Lua or keep them around.
- Use `const char*`, `char*`, or `std::string_view` only as push-time
  convenience inputs.

Luacxx intentionally does **not** expose a general `Get<const char*>` or
`Store<const char*>` path anymore.

## `std::string`

Luacxx handles `std::string` as an owned Lua string conversion.

Push behavior:

- `lua::push(state, std::string(...))` copies the string bytes into a Lua string

Read behavior:

- `lua::get<std::string>(...)` copies bytes back into a C++ `std::string`
- `lua::store(std::string&, ...)` does the same for an existing string

This is the safe default because the C++ object owns its own storage after the
conversion.

## Push-Only String Inputs

Luacxx also accepts a few non-owning string-like inputs when pushing to Lua:

- `const char*`
- `char*`
- `std::string_view`
- string literals / char arrays

These are convenience inputs only. They all end up pushing a Lua string.

That means:

- Lua receives string data, not a live C buffer
- mutability is not preserved
- pointer identity is not preserved

So `char*` here should be read as “push this as a string,” not “Lua can modify
this buffer.”

## Why `const char*` Is Not A General Read Type

Lua strings are owned by Lua.

When you ask Lua for a raw `const char*`, the pointer you get is only a borrowed
view into Lua-managed string storage. That creates lifetime hazards:

- the pointer is not owned by C++
- its validity depends on the Lua state and value lifetime
- keeping it around is easy to get wrong

For that reason, Luacxx's public string read path is centered on `std::string`
instead.

## The Raw Lua Escape Hatch

If you really do want a borrowed C string view from Lua, use the raw Lua C API
directly and take responsibility for the lifetime yourself.

The main functions are:

### `lua_pushstring(state, const char*)`

Pushes a null-terminated C string to Lua.

### `lua_pushlstring(state, data, len)`

Pushes a byte string of explicit length.

This is what you want when:

- the data is not null-terminated
- the string may contain embedded null bytes
- you already have a `std::string_view`

### `lua_tolstring(state, index, &len)`

Returns a borrowed pointer to Lua string data and its length.

This is the lowest-level escape hatch if you truly want a borrowed `const char*`
view from Lua.

### `lua_tostring(state, index)`

Equivalent to `lua_tolstring` when you do not need the length.

This is convenient, but `lua_tolstring` is usually clearer and safer because it
makes the byte length explicit.

## When The Raw Escape Hatch Makes Sense

Use the raw Lua string APIs directly when:

- you need a borrowed string view only for immediate local use
- you need exact byte lengths
- you are integrating with an API that already expects `const char*`
- you are working in low-level Lua-facing code and know the lifetime constraints

Prefer `std::string` when:

- the value escapes the current statement or function
- you want ownership on the C++ side
- you are writing normal binding code rather than low-level runtime plumbing

## Rule Of Thumb

- `std::string` is the default string type.
- `std::string_view` is a good push-only convenience input.
- C strings are fine to push, but not the main readback API.
- If you truly need borrowed `const char*`, use raw Lua string functions directly.

## Related Docs

- [Standard Library Types](standard-library-types.md)
- [Useful Lua Functions](useful-lua-functions.md)
- [Conversion Templates](conversion-templates.md)
