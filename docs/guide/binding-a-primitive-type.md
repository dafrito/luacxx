# Binding a Primitive Type

This guide shows the smallest useful Luacxx extension point: teaching Luacxx
how to push and read a type that behaves like a value.

For a primitive or value-like type, the main tools are:

- `lua::Push<T>`
- `lua::Store<T>`
- optionally `lua::Get<T>`

## Example: `ColorChannel`

Suppose you have a tiny type that wraps an integer:

```cpp
struct ColorChannel
{
    int value;
};
```

You can map it to Lua as a number.

## Push To Lua

Define `Push<ColorChannel>` to convert the C++ value into a Lua value:

```cpp
template <>
struct lua::Push<ColorChannel>
{
    static void push(lua_State* const state, const ColorChannel& source)
    {
        lua_pushinteger(state, source.value);
    }
};
```

After that, this works:

```cpp
ColorChannel red{255};
lua::push(state, red);
```

## Store From Lua

Define `Store<ColorChannel>` to read a Lua value back into an existing C++
object:

```cpp
template <>
struct lua::Store<ColorChannel>
{
    static void store(ColorChannel& destination, lua_State* const state, const int pos)
    {
        destination.value = lua::get<int>(state, pos);
    }
};
```

Now you can write:

```cpp
ColorChannel channel{0};
lua::store(channel, state, 1);
```

## Optional `Get<T>`

Often you do not need a custom `Get<T>`. The default `lua::get<T>()` path can
build on `Store<T>`.

If you want a direct `get` specialization anyway, it can look like this:

```cpp
template <>
struct lua::Get<ColorChannel>
{
    static ColorChannel get(lua_State* const state, const int pos)
    {
        ColorChannel result{};
        lua::Store<ColorChannel>::store(result, state, pos);
        return result;
    }
};
```

## Exposing A Function That Uses The Type

Once the conversion exists, bound functions can use the type naturally:

```cpp
ColorChannel clamp_channel(ColorChannel input)
{
    if (input.value < 0) {
        return {0};
    }
    if (input.value > 255) {
        return {255};
    }
    return input;
}

void open_color(lua_State* const state)
{
    lua::thread env(state);
    env["clamp_channel"] = clamp_channel;
}
```

Luacxx can then marshal the argument and result through your conversion.

## When To Use This Pattern

This is a good fit when:

- the type has value semantics
- the Lua representation is simple
- you do not need userdata identity or methods

Examples include:

- small enums or enum-like wrappers
- numeric wrappers
- tiny structs that naturally map to a number, string, or table

If the type needs methods, identity, or lifetime management, a userdata-backed
class binding is usually a better fit.

## Related Docs

- [Binding a Class](binding-a-class.md)
- [Writing Bindings](writing-bindings.md)
- [Useful Lua Functions](useful-lua-functions.md)
