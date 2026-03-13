# Iterating Stack Values With `lua::range`

`lua::range<T>` is a small helper for treating the current Lua stack like an
iterable sequence of converted C++ values.

It is mostly a convenience wrapper around `lua::iterator<T>`.

## Basic Use

```cpp
int sum(lua_State* state)
{
    int total = 0;
    for (int value : lua::range<int>(state)) {
        total += value;
    }
    return total;
}
```

That iterates from stack slot `1` through `lua_gettop(state)`.

## What It Does

For each stack slot, `lua::iterator<T>` reads the value through
`lua::Get<T>::get(state, pos)`.

So this:

```cpp
for (std::string text : lua::range<std::string>(state)) {
    // ...
}
```

is essentially a cleaner spelling of:

```cpp
for (int pos = 1; pos <= lua_gettop(state); ++pos) {
    std::string text = lua::get<std::string>(state, pos);
    // ...
}
```

## When It Helps

`lua::range<T>` is a nice fit when:

- you want to consume all arguments as the same type
- you are writing a reduction like sum/join/all/any
- you want range-for syntax instead of manual stack loops

## When Not To Use It

It is less useful when:

- arguments have mixed types
- you need direct access to positions or type tags
- you want to mutate the stack while iterating

In those cases, `lua::index` or raw Lua stack APIs are usually a better fit.

## Relation To `lua::index`

`lua::range<T>` is the typed homogeneous iteration helper.
`lua::index` is the lower-level stack-slot wrapper.

If you need:

- homogeneous iteration: use `lua::range<T>`
- stack-slot access and navigation: use `lua::index`

## Related Docs

- [Working With The Lua Stack](working-with-the-lua-stack.md)
- [Working With `lua::index`](working-with-index.md)
- [Conversion Templates](conversion-templates.md)
