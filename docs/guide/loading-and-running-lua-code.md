# Loading And Running Lua Code

Luacxx splits "load" and "run" in the same way Lua itself does.

- `load_*` compiles Lua code and gives you a callable chunk
- `run_*` loads it and immediately executes it

## `lua::load_string`

`lua::load_string(state, code)` compiles a string of Lua source and returns a
`lua::index` pointing at the resulting chunk on the stack.

```cpp
lua::index chunk = lua::load_string(env, "return 2 + 2");
```

At that point the chunk is just a function. It has not run yet.

## `lua::load_file`

`lua::load_file(...)` does the same thing for a file or stream:

```cpp
lua::index chunk = lua::load_file(env, "script.lua");
```

Luacxx supports:

- `std::string` filenames
- `const char*` filenames
- `std::istream`

If compilation fails, it throws `lua::error`.

## Running The Loaded Chunk

Once you have a loaded chunk, call it like any other Lua callable:

```cpp
lua::index chunk = lua::load_string(env, "return 2 + 2");
int answer = lua::call<int>(chunk);
```

You can also use `lua::invoke(...)` when you want lower-level control over
results left on the stack.

## `lua::run_string`

`lua::run_string(...)` is the convenience form that loads and runs in one step:

```cpp
lua::run_string(env, "print('hello')");
int answer = lua::run_string<int>(env, "return 2 + 2");
```

The typed form expects one return value and converts it with `lua::get<RV>`.

## `lua::run_file`

`lua::run_file(...)` is the file equivalent:

```cpp
lua::run_file(env, "setup.lua");
int answer = lua::run_file<int>(env, "math.lua");
```

## When To Use Load vs Run

- use `load_*` when you want the chunk as a reusable callable
- use `run_*` when you just want to execute the code immediately

That distinction matters if you want to:

- cache a chunk
- call it multiple times
- inspect or store the callable before invoking it

## Errors

Both loading and running can throw `lua::error`:

- syntax/compile problems during load
- runtime problems during invocation
- Luacxx-side checks such as "expected a result value"

## Streams And Files

The stream overload of `lua::load_file` is useful when the source code does
not naturally come from a path on disk.

Luacxx also handles shebang-prefixed Lua source in the stream/file path.

## Related Docs

- [Handling `lua::error`](handling-lua-errors.md)
- [Working With Callables](working-with-callables.md)
- [Working With The Lua Stack](working-with-the-lua-stack.md)
