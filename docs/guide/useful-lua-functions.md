# Useful Lua Functions

This guide collects the Lua C API functions that Luacxx refers to often in its
own implementation and examples. These notes used to live inline in the
headers; keeping them here makes them easier to find without turning the
headers into tutorials.

## Creating And Initializing States

### `luaL_newstate()`

Creates a fresh Lua state using Lua's default allocator. It does not load the
standard libraries by itself.

### `lua_newstate(lua_Alloc allocator, void* allocator_data)`

Creates a Lua state with a custom allocator. This is the lower-level entry
point when you need control over runtime allocation behavior.

### `lua_newthread(lua_State*)`

Creates a Lua thread sharing the same global environment as the given state.
The new thread is pushed onto the stack and is owned by the parent state for
garbage-collection purposes.

### `luaL_openlibs(lua_State*)`

Loads the standard Lua libraries into the state.

### `lua_close(lua_State*)`

Closes the state, releases memory, and runs relevant finalizers. If called on a
Lua thread, it closes the owning state and all related threads.

## Stack Indexing

### `lua_absindex(state, index)`

Converts a relative stack index such as `-1` into a stable absolute index.
This is especially useful when you are going to push more values and want the
original index to remain valid.

### `LUA_REGISTRYINDEX`

The registry pseudo-index. Luacxx uses it for cached metatables, references,
and a few internal facilities.

### `lua_gettop(state)`

Returns the current top index of the stack.

For a non-empty stack, `lua_absindex(state, -1)` is the same position as
`lua_gettop(state)`.

### `lua_settop(state, top)`

Adjusts the top of the stack. This is the fastest way to clear unwanted values
or reset the stack to a known size.

## Rearranging The Stack

### `lua_copy(state, source, dest)`

Copies a value from one stack slot to another without removing the source.

### `lua_replace(state, index)`

Moves the topmost value into `index` and pops the original top.

This is a common way to place a return value into slot `1` and then trim the
rest of the stack.

That leads to a common return-value pattern:

```cpp
lua_pushstring(state, "No time.");
lua_replace(state, 1);
lua_settop(state, 1);
return 1;
```

### `lua_remove(state, index)`

Removes the value at the given index and shifts everything above it down by
one. This is linear-time work, so it is often better to prefer `lua_settop()`
or a different calling pattern when performance matters.

### `lua_insert(state, index)`

Moves the topmost value to the given position, shifting the values at and above
that position upward.

### `lua_pop(state, n)`

Pops `n` values from the top of the stack.

## Strings

### `lua_pushstring(state, const char*)`

Pushes a null-terminated C string to Lua.

### `lua_pushlstring(state, data, len)`

Pushes a string with an explicit byte length.

This is the right choice when the source is not null-terminated or may contain
embedded null bytes.

### `lua_tolstring(state, index, &len)`

Returns a borrowed pointer to Lua-managed string data and writes its length.

This is the raw escape hatch if you truly want `const char*` access instead of
Luacxx's preferred `std::string` path.

### `lua_tostring(state, index)`

Like `lua_tolstring`, but without an explicit output length.

## Why These Matter In Luacxx

Luacxx does not try to hide Lua's stack model. The wrappers are designed to
compose with these functions, not replace them entirely. If you are extending
Luacxx or writing custom bindings, understanding these Lua primitives will make
the higher-level helpers much easier to use correctly.
